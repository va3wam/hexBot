// This is the file flows.cpp, which lives in the include directory
// and is invoked by an include statement in main.cpp
// routines here have corresponding entries in include/flows.h
//
// TODO: #46 follow doxygen standards

#include <flows.h>               // including main.h
void setupFlows()
{  // initialize params for the accumulation of flow rows from MQTT FLOW commands
   f_active = 0;      // what row number we fill next, and also the count of rows seen for current flow
                              // set up leg info that's indexable by leg number from 1 to 6
   legIndexDriver[1] = 0;     // leg #1's river is 0, like whole right side
   legIndexDriver[2] = 0;
   legIndexDriver[3] = 0;
   legIndexDriver[4] = 1;     // and driver for the right side is 1
   legIndexDriver[5] = 1;
   legIndexDriver[6] = 1;

   legIndexHipPin[1] = 0;     // leg 1's hip servo is on pin 0 of it's PWM driver
                              // knee pin = hip pin +1, ankle pin = hip pin +2
   legIndexHipPin[2] = 3;     // leg 2's hip pin
   legIndexHipPin[3] = 6;     // and so on
   legIndexHipPin[4] = 0;
   legIndexHipPin[5] = 3;
   legIndexHipPin[6] = 6;

// global coords for each leg's home position
   f_homeX[1] =  18.62 ; f_homeY[1] = -14.79 ; f_homeZ[1] = -10.60 ; 
   f_homeX[2] =   0    ; f_homeY[2] = -20.71 ; f_homeZ[2] = -10.60 ;
   f_homeX[3] = -18.62 ; f_homeY[3] = -14.79 ; f_homeZ[3] = -10.60 ;
   f_homeX[4] =  18.62 ; f_homeY[4] =  14.79 ; f_homeZ[4] = -10.60 ;
   f_homeX[5] =   0    ; f_homeY[5] =  20.71 ; f_homeZ[5] = -10.60 ;
   f_homeX[6] = -18.62 ; f_homeY[6] =  14.79 ; f_homeZ[6] = -10.60 ;

// global coords for each leg's hip position
   f_hipX[1] = 8.87;  f_hipY[1] = -5.05;     
   f_hipX[2] =   0 ;  f_hipY[2] = -6.94;
   f_hipX[3] =-8.87;  f_hipY[3] = -5.05;
   f_hipX[4] = 8.87;  f_hipY[4] =  5.05;
   f_hipX[5] =   0 ;  f_hipY[5] =  6.94;
   f_hipX[6] =-8.87;  f_hipY[6] =  5.05;

   legNum[1] = "1" ;       // crude way to convert leg numbers to strings via lookup
   legNum[2] = "2" ;       // ..for safe toe position checking in flows.cpp:PrepNextLine()
   legNum[3] = "3" ;
   legNum[4] = "4" ;
   legNum[5] = "5" ;
   legNum[6] = "6" ;
}

// standard doxygen docs here

/**
 * @brief Convert target degrees to a PWM value.
 * @details Translate a desired servo position expressed in degrees to a PWM 
 * number to feed the servo if degrees is on a scale from 0 to 180, the center 
 * position is 90 degrees, specified in centerDeg if degrees is on a scale from 
 * -90 to +90, the center position is 0, which goes in centerDeg the equivalent 
 * PWM value is returned in integer parameter outPWM using a horn with 24 
 * positions allows positioning +/- 15 degrees using a 25 poistion horn with 
 * reversing allows an accuracy of +/- 7.5 degrees.
 * 
 * At this level of accuracy, we can treat the current servo motors as 
 * identical, all with North = 300, East = 115, and West = 486.
 * 
 * The servos aren't perfectly linear, and the PWM value may be off by as much 
 * as 3.9, which is equivalent to a maximum error of less than 2 degrees.
 * 
 * @param degrees Target angle for motor.
 * @param centreDeg Mid point of motor movement range.
 * @return PWM value.
 * ==========================================================================*/
int32_t mapDegToPWM(float degrees, float centerDeg)
{
   const float offset = 90; // Angle offset of motor in neutral position?
   // TODO #26 create constants for all magic numbers in this function. 
   // range check the desired degrees value
   float fixup = 0;       // assume degrees is within range defined by offset
   if(degrees < centerDeg - offset)  { fixup = offset - degrees; } 
   if(degrees > centerDeg + offset)  { fixup = offset - degrees; }
   // formula fits a line to two measured data points (x=degrees, y=PWM) with 
   // the points selected to minimize overall errors: (24,160) (166,460)
   // formula is based on y = M * x + b where M is the slope, 
   // (delta Y)/(delta X) for 2 selected points, b is the y intercept, derived 
   // by substituting a selected point into above formula after slope is known.
   return (degrees - (centerDeg - offset + fixup)) * 300 / 142 + 109.3;
} // mapDegToPWM()

/**
 * @brief Convert hip, knee and ankle joint angles to toe X,Y,Z coordinates.
 * @param Hip angle in degrees.
 * @param Knee angle in degrees.
 * @param Ankle angle in degrees.
 * @param *toeX address where the X coordinate of the toe is stored.
 * @param *toeY address where the Y coordinate of the toe is stored.
 * @param *toeZ address where the Z coordinate of the toe is stored.
 * @return converted coordinates for the toe are written to the memory 
 * locations passed as arguments to this function and can therefore be 
 * accessed directly by the calling function.
 * ==========================================================================*/
void anglesToCoords(float hip, float knee, float ankle, float *toeX, float *toeY, float *toeZ)
{
   *toeX = (origXOffset + shinLen * cos(radians(knee)) + footLen *sin(radians(ankle - knee + toeOffset))) * cos(radians(hip));
   *toeY = -shinLen * sin(radians(knee)) - footLen * cos(radians(ankle - knee + toeOffset));
   *toeZ = sin(radians(hip)) * (origXOffset + shinLen * cos(radians(knee)) + footLen * sin(radians(ankle - knee + toeOffset)));
} // anglesToCoords()

/**
 * @brief Convert toe X,Y,Z coordinates to hip, knee and ankle joint angles.
 * @param x toe x coordinate in cm.
 * @param y toe y coordinate in cm.
 * @param z toe z coordinate in cm.
 * @return converted angles for the hip, knee and ankle are written to the 
 * global variables f_angH, f_angK and f_angA and can therefore be 
 * accessed directly by the calling function.
 * ==========================================================================*/
void coordsToAngles(float Tx, float Ty, float Tz)    
{
   // results are returned in f_angH, f_angK and f_angA
   // TODO #27 create constants for all magic numbers in this function.
   // documentation for this routine is found in the file: docs/explain-angles-from-coords.odt
   // see also the spreadsheet formulas-angles-from-coords.ods

   float Ux, Uy;        // toe position when rotated into xy plane.
   float C1, C2;        // coefficients used to reduce algebraic complexity
   float QA, QB, QC;    // Quadratic coefficients for Ax^2 + Bx +C =0
   float DET;           // determinant in quadratic formula
   float Ax, Ay;        // coordinates of ankle after rotation to local XY plane

   // hexbot body measurements
   const float BT = 2.915 ;   // thigh length (between hip and knee, horizontally)
   const float BS = 7.620 ;   // shin length (between knee and ankle)
   const float BF = 11.059;   // foot length (diagonal between ankle and toe)
   const float BTOA = 17.063; // toe offset angle = angle between ankle servo vertical, and toe, in degrees
   // const float BTOD = 3.245;  // toe offset distance. perpendicular distance from toe to ankle servo vertical line

   f_angH = degrees( atan2(Tz, Tx) ) ;       // the hip angle is the easy one.

   // now reduce to a 2D problem by rotating leg into xy plane (around y axis)
   Ux = Tx * cos(radians(- f_angH)) - Tz * sin(radians(- f_angH));
   Uy = Ty; // the rotation doesn't change the y value
 sp3sl("Ux,Uy= ",Ux,Uy);  
   // documentation explains the use of 2 coefficients to simplify the algebra
   C1 = BS * BS - BF * BF + Ux * Ux + Uy * Uy - BT * BT ;
   C2 = 2 * BT - 2 * Ux ;
sp3sl("C1,C2= ",C1,C2);
   // the equations of 2 intersecting circles reduces to a quadratic equation for Ax
   // calculate the quadratic coefficients for A*x^2 + B*x +c = 0
   QA = 1 + (C2 * C2) / (4 * Uy * Uy) ;
   QB = (-2 * BT) + (2 * C1 * C2) / (4 * Uy * Uy);
   QC = BT * BT + (C1 * C1) / (4 * Uy * Uy) - BS * BS;
sp3s("QA, QB, QC = ",QA,QB);sp1l(QC);
   // The x quadratic solution is the ankle's x coordinate, and will be referred to as Ax
   // We'll optimistically use the plus case choice for the "plus or minus" in the quadratic solution...
   //   x = (-B +/- SQRT( B*B - 4 * A * C) / (2 * A)
   DET = round(( QB * QB - 4 * QA * QC) * 10000) / 10000 ;  //if roundoff error causes a tiny -Ve #, SQRT barfs
sp2sl("determinant= ",DET);
   if(DET < 0) {Log.noticeln("=== negative determinant in coordsToAngles === %d", DET) ; };
   Ax = ( -QB + sqrt( DET)) / (2 * QA) ;
   Ay = (BS*BS - BF*BF + Ux*Ux + Uy*Uy - BT*BT + Ax*(2*BT - 2*Ux)) / (2*Uy) ; // derived by substituting x in earlier equation
   // maybe do some sanity checks to see if we should be using the minus case in the quadratic slution
       //    if(f_AyMinus > f_AyPlus && f_AxMinus >= origXOffset)
       //    if that puts x to the -ve side of knee, where ankle can't go, pick the other case
       //   if(f_Ax < origXOffset)

    // now that we know where the ankle is, we can finally work on the angles
    // the knee is easy since we defined the ankle position above
    // could use old formula: f_angK = -1 * asin(radians(f_Ay / shinLen)) , or...
    f_angK = degrees( atan2(-Ay,(Ax - BT)) );

    // the ankle angle needs to reflect the 17 degree offset within the "foot"
    f_angA = degrees( atan2( Ux - Ax, Ay - Uy)) - BTOA ;
   
} // coordsToAngles()

bool globCoordsToLocal(int legNumber, float gx, float gy, float gz, float *lx, float *ly,float *lz)
{
//   leg numbers: 1=FrontRight, 2=MR, 3=BR, 4=FrontLeft, 5=ML, 6=BL
   float Xrt, Yrt ;  //tem variables for rotated global X & Y coords

   *ly = gz;       // height above robot is global Z, local Y
   switch (legNumber) 
   {
      case 1:
        // Front Right leg
        Xrt = cos_m45 * (gx-fp_frontHipX) - sin_m45 * (gy + fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_m45 * (gx-fp_frontHipX) + cos_m45 * (gy + fp_frontHipY);
        *lx = -1 *Yrt;
        *lz = Xrt;
        break;
      case 2:
        // Middle Right leg
        *lx = -1 * gy - fp_sideHipY;
        *lz = gx;
        break;
      case 3:
        // Back Right leg
        Xrt = cos_p45 * (gx + fp_frontHipX) - sin_p45 * (gy + fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_p45 * (gx + fp_frontHipX) + cos_p45 * (gy + fp_frontHipY);
        *lx = -1 * Yrt;
        *lz = Xrt;        
        break;
      case 4:
        // Front Left leg
        Xrt = cos_p45 * (gx - fp_frontHipX) - sin_p45 * (gy - fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_p45 * (gx - fp_frontHipX) + cos_p45 * (gy - fp_frontHipY);
        *lx = Yrt;
        *lz = Xrt * -1.;        
          
        break;
      case 5:
        // Middle Left leg
        *lx = gy - fp_sideHipY;
        *lz = gx * -1;
        break;
      case 6:
        // Back Left leg
        Xrt = cos_m45 * (gx + fp_frontHipX) - sin_m45 * (gy - fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_m45 * (gx + fp_frontHipX) + cos_m45 * (gy - fp_frontHipY);
sp2s("---Xrt, Yrt: ",Xrt); sp; sp1l(Yrt);
        *lx = Yrt;
        *lz = Xrt * -1.;        
        break;
      default:
        return false;
   }
   return true;
}

// do_flow is enabled by the MQTT flow_go command, which sets f_flowing to true
// f_flowing is checked in loop() and calls do_flow() on every loop, if it's enabled
// f_active is initially zero, which initiates various setup activities on first do_flow entry
// in general case, do_flow executes a small servo movement on all 18 servos, at a calculated time interval

void do_flow()          // called from loop if there's a flow executing that needs attention
{
   if(f_active == 0)                // starting a new flow, so need to do some setup
   {
//      sp1l("--initial flow toe numbers--");
//      for(L=1; L<=6; L++)     // copy flow coords from flow row [0] into  working vectors
//      {  sp2s(f_legX[0][L],f_legY[0][L]); sp2l(" ",f_legZ[0][L]);
//      }
      // we need local coords to be able to give commands to servos
      // the operation code in f_operation[f_active] tells us what king of coords we were given
      f_goodData = true;               // assume thing will go well, & f_operation is valid
      prepNextLine();         // get local coords of position in active flow row in f_endlegX[L], Y, Z

      if(f_goodData)
      {  // f_endLegX[leg],Y,Z arrays contain the local coords of the position we need to jump to
         for(L=1; L<=6; L++)
         {  // move each leg to the position in local coords in f_endLegX[l], f_endLegY[l], f_endLegZ[l]
            // the call that actually moves servo is pwmDriver[driver].setPWM[pin, pwmClkStart, pwm-value]
            //   the driver we can lookup in legIndexDriver[leg]
            //   the pin can be derived from legIndexHipPin[leg]
            //   to get pwm value, we convert local coords to angles, then from angles to pwm values

//            Log.noticeln(" X: %F, Y: %F, Z: %F",f_endLegX[L], f_endLegY[L], f_endLegZ[L]);
//  ==============================================================================================================
            coordsToAngles(f_endLegX[L], f_endLegY[L], f_endLegZ[L]); 
            Log.noticeln("<do_flow> Leg %u, angH = %F, angK = %F, angA = %F",L,f_angH,f_angK,f_angA);
            f_lastAngH[L] = f_angH;       // remember angles so we can skip redundant moves in future
            f_lastAngK[L] = f_angK;
            f_lastAngA[L] = f_angA;

            // now, one servo wihin the leg at a time, figure the pwm value, and move the servo
            // starting with the hip...
            int legstart = micros();  // timestamp start of leg movement
            pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L],  pwmClkStart, mapDegToPWM(f_angH,0));
//            Log.noticeln("H: Driver=%d,  Pin=%d, angH=%F,  pwm=%d",legIndexDriver[L],legIndexHipPin[L],f_angH, mapDegToPWM(f_angH,0));
            pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+1,pwmClkStart, mapDegToPWM(f_angK,0));
//            Log.noticeln("K: Driver=%d,  Pin=%d, angH=%F,  pwm=%d",legIndexDriver[L],legIndexHipPin[L]+1,f_angK, mapDegToPWM(f_angK,0));
            pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+2,pwmClkStart, mapDegToPWM(f_angA,0));
//            Log.noticeln("A: Driver=%d,  Pin=%d, angH=%F,  pwm=%d",legIndexDriver[L],legIndexHipPin[L]+2,f_angA, mapDegToPWM(f_angA,0));
sp2l(" legStart time= ",micros()-legstart);

            f_lastLegX[L] = f_endLegX[L];   // remember this initial location as start of next line
            f_lastLegY[L] = f_endLegY[L];
            f_lastLegZ[L] = f_endLegZ[L];
            // ok, the 3 servos in that leg have been moved - on to the next leg
         }  // for l = 1 to 6
         //at this point, all legs have been moved to the initial position in the flow
         // well, move commands have been sent. pause a bit for the servos to actually move
         delay(340);             // in theory, wost case is about 120 degrees, & servo does 60 degrees in .17 sec
         // start preparing for frame by frame moves from this positon to next one in flow, i.e. [1] in flow rows
         // first, figure out local coords of that next position, like we did for initial position
         if(f_count > 1 )     // is there at least one more flow row?
         {                    // yup - set up to do frames to get to it
            sp1l("--initial flow toe numbers for flow row 1--");
            for(L=1; L<=6; L++)     // display flow coords from flow row [1] into  working vectors
            {  sp2s(f_legX[1][L],f_legY[1][L]); sp2l(" ",f_legZ[1][L]);
            }
            // we need local coords to be able to give commands to servos
            // the operation code in f_operation[f_active] tells us what king of coords we were given
            f_active=1;             // OK, we're now processing flow row 1 for first real line
            prepNextLine();         // decode flow row 1's position, figure deltas, etc
                                    // so we'll be ready at next 20 ms mark
            f_frame = 1 ;           // initialize frame counter
            f_framesPerPosn = int(f_msecs[1] / f_msecPerFrame + .5);  // rounded count of how many fraes fit in time)
         } // if f_count > 1
         else  // if f_count > 1. else case  means only initial position was given in flow
         {  f_flowing = false;      // stop flow processing
         }
      }  // if(goodData)
      else   // f_goodData was false - abort flow
      {    f_flowing = false;         // stop executing the flow
      }
      
   } // if f_active == 0
// =================================================
// =================================================
// =================================================

   // OK above takes care of initial case for initial flow row where flow is just starting
   // now the work of grinding out the servo changes for everu 20 msec frame, fo 6 legs
   else if( f_active > 0)
   {  if(millis() >= f_nextTime)          // did we get to next 20 msec frame time?
      {                                   // we did hit 20 ms mark - time to move servos
//sp2l("===f_active ",f_active);
                                          // (otherwise exit immediately & wait)
         f_nextTime = millis() + f_msecPerFrame;    // yup, quickly reset for next 20 msec interval
//sp2("=== working frame= ",f_frame); sp2("   fPrPosn= ",f_framesPerPosn);
         for(L=1; L<=6; L++)              // use frame count to figure next frame position
         {  f_tmpX = (float)f_frame * f_deltaX[L] / (float)f_framesPerPosn + f_lastLegX[L];
            f_tmpY = (float)f_frame * f_deltaY[L] / (float)f_framesPerPosn + f_lastLegY[L];
            f_tmpZ = (float)f_frame * f_deltaZ[L] / (float)f_framesPerPosn + f_lastLegZ[L];
            coordsToAngles(f_tmpX, f_tmpY, f_tmpZ); // creates f_angH, f_angK, f_angA

            // now, one servo within the leg at a time, figure the pwm value, and move the servo
            // starting with the hip...
            if((toeMoveAction & fa_moveServos) != 0)    // did flow_go command options tell us to move servos?
            {  if(f_angH != f_lastAngH[L])               // if new hip angle is different than last one, move the servo 
               {  pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L],  pwmClkStart, mapDegToPWM(f_angH,0));
                  f_lastAngH[L] = f_angH;                // and update last angle for this servo
               }
            }
            if((toeMoveAction & fa_moveServos) != 0)    // did flow_go command options tell us to move servos?
            {  if(f_angK != f_lastAngK[L])               // only if the knee angle has changed...
               {  pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+1,pwmClkStart, mapDegToPWM(f_angK,0));
                  f_lastAngK[L] = f_angK;
               }
            }
            if((toeMoveAction & fa_moveServos) != 0)    // did flow_go command options tell us to move servos?
            {  if(f_angA != f_lastAngA[L])               // only if ankle angle has changed...
               {  pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+2,pwmClkStart, mapDegToPWM(f_angA,0));
                  f_lastAngA[L] = f_angA;
               }
            }
            if((toeMoveAction & fa_dispPWM) != 0)    // if flow go command options told us to display PWM..
            {  sp2s(mapDegToPWM(f_angH,0),mapDegToPWM(f_angK,0));sp;sp1s(mapDegToPWM(f_angA,0)); sp;
            }
            if((toeMoveAction & fa_dispAngles) != 0) // if flow_go command options told us to display angles..
            {  sp2s(f_angH,f_angK); sp; sp1s(f_angA); sp;
            }
            if((toeMoveAction & fa_dispLocal) != 0) // if flow_go command options told us to display local coords..
            {  sp2s(f_tmpX,f_tmpY); sp; sp1s(f_tmpZ); sp; 
            }
         }  //for L=1...
         // output gets messy if you display more than one attribute at a time - avoid that
         if((toeMoveAction & (fa_dispPWM + fa_dispAngles + fa_dispLocal)) != 0)  // if we displayed numbers
         {  nl;                              // then output the final new line
         }
         f_frame ++  ;                          // advance to next frame within the flow row
//sp2l("=== new frame ",f_frame);
         if(f_frame > f_framesPerPosn)          // did we run out of frames?
         {  // yup - we must be sitting at end position of the line, otherwise wait for next 20 msec
            f_active = f_active + 1 ;                       // advance to next flow row
//sp2l("=== new f_active ",f_active);
            if(f_active < f_count)              // have we run out of flow rows to do?
            {
              for(L=1; L<=6; L++)              // no, remember end of last line as start of next one
               {  f_lastLegX[L] = f_endLegX[L];
                  f_lastLegY[L] = f_endLegY[L];
                  f_lastLegZ[L] = f_endLegZ[L];
               }
               f_goodData = true;               // assume thing will go well, & f_operation is valid
               prepNextLine();                  // process active flow row, leaving local coords in f_endLegX[L], Y, Z
            }                                   // ..and figuring frame deltas, and framesPerPosition
            else                                // we ran out of rows in the flow. end flow processing
            {
               f_flowing = false;               // stop flow processing triggered from loop()
               f_nextTime=0;                    // kill any 20 ms processing
            }
         } // if(f_frame > f_framesPerPosn) 
      }   // if millis > f_nextTime
   } // else if( f_active > 0)
   else
   {
     // f_active went negative - abort
     f_flowing = 0;
   }

}  // void do_flow

// ================================================================================

bool prepNextLine()  
// prepare for next line that goes from position in last flow row to one in current flow row
// which is identified by row number in f_active
// actions, all taken for each leg:
// - figure global coords of the end point of the line, which could be given as absolute global coords,
//   or as an offset from home position, depending of the f_operation value in the flow row
// - translate from global coords to local coords for each leg. left in f_endLegX[L],Y,Z arrays
// - safety check that requested toe position is within the safety box around the home position
// - calculate the number of Frames needed to do the line, based on specified time duration
// - calculate the deltas to be travelled in the X, Y, and Z directions
// NOT done in this routine, but needed to actually move the legs
//          - translate local coordinates to servo angles
//          - translate servo angles to PWM integer values
//          - feed the PWM values to the servers

{  // initialize to start doing frame moves in the line between
   // previous flow row's position: lastLegX[L], Y, Z
   // this flow row's (identified by f_active) position: f_legX[f_active][L], Y, Z
   // local coords of end point of line are left in f_endLegX[L], Y, Z
   // f_operation in flow row tells us what kind of numbers are given for each leg

   f_goodData = true;  // initially assume all will go well
   if(f_operation[f_active] == fo_moveRelHome || f_operation[f_active] == fo_startRelHome)
   {  // we were given offsets relative to home position, so add in home coords
//      sp1l("--global toe coords including offsets--");
      for(L=1; L<=6; L++)  // add offset to home's global coord, to get final global coord
      {  f_tmpX = f_legX[f_active][L] + f_homeX[L];   
         f_tmpY = f_legY[f_active][L] + f_homeY[L];
         f_tmpZ = f_legZ[f_active][L] + f_homeZ[L];
         // then convert global coords to local coords
         globCoordsToLocal(L,f_tmpX,f_tmpY,f_tmpZ,&f_endLegX[L],&f_endLegY[L],&f_endLegZ[L]);
          sp1s("***tmpX: ");sp2s(f_tmpX,f_tmpY); sp2l(" ",f_tmpZ);
          sp1s("===Lxyz: ");sp2s(f_endLegX[L],f_endLegY[L]); sp2l(" ",f_endLegZ[L]);
      }
   }
   else if (f_operation[f_active] == fo_moveAbs || f_operation[f_active] == fo_startAbs)
   {  // we were given absolute coords, and need to convert to local coords
      for(L=1; L<=6; L++)   // l stands for leg. short to avoid cobol expression syndrome
      {  globCoordsToLocal(L,f_legX[f_active][L],f_legY[f_active][L],f_legZ[f_active][L],
            &f_endLegX[L],&f_endLegY[L],&f_endLegZ[L]);
      }
   }
   else if (f_operation[f_active] == fo_moveLocal)   // does flow row contain local cords?
   {  // yup, we were given the local coordinate that we need, so just copy them
      for(L=1; L<=6; L++) 
      { f_endLegX[L] = f_legX[f_active][L];   // get local coords right out of flow row
        f_endLegY[L] = f_legY[f_active][L];
        f_endLegZ[L] = f_legZ[f_active][L];
      }
   }
   else
   {  // unsupported op code in nextfirst row - abort
      f_flowing = false;         // stop executing the flow
      f_goodData = false;        // bypass rest of do_flow processing
      // need to avoid falling into following code. use a flag for "good data seen" ?
   }
   if(f_goodData)       // continue only if we haven't aborted due to an error
   {
      // get here if we've been able to calculate local coordinates for next toe position
      // now we need to see if requested position is within "safe positions box"
      String badLegs = "" ;   // error message identifying unsafe positions
      for(L=1; L<=6; L++ )       // go thru all legs
      { 
sp2s(f_endLegX[L],f_endLegY[L]); sp; sp1l(f_endLegZ[L]);
         if(f_endLegX[L] - f_localHomeX > safeMaxPosX){ badLegs = badLegs + legNum[L] + "XP ";}
         if(f_localHomeX - f_endLegX[L] > safeMaxNegX){ badLegs = badLegs + legNum[L] + "XN ";}
         if(f_endLegY[L] - f_localHomeY > safeMaxPosY){ badLegs = badLegs + legNum[L] + "YP ";}
         if(f_localHomeY - f_endLegY[L] > safeMaxPosY){ badLegs = badLegs + legNum[L] + "YN ";}
         if(f_endLegZ[L] - f_localHomeZ > safeMaxPosZ){ badLegs = badLegs + legNum[L] + "ZP ";}
         if(f_localHomeZ - f_endLegZ[L] > safeMaxPosZ){ badLegs = badLegs + legNum[L] + "ZN ";}
      }  // for L=1...
      if(badLegs != "")             // if any safety violation ocurred..
      {  f_goodData = false;        // abort further processing of the flow row
         f_flowing = false;         // and stop fow processing
         sp2l("****************** toe safety violation(s) [<leg><coord><positive or negative side> : ",badLegs);
      } // if badLegs != ""
      else if(f_active != 0)     // first flow is special case with direct jump rather than frames
      {  // figure deltas for end points on movement lines for each leg, for each axis
         for(int L=1; L<=6; L++)   // L stands for leg. short to avoid cobol expression syndrome
         {  f_deltaX[L] = f_endLegX[L] - f_lastLegX[L]; //travel needed in local X direction
            f_deltaY[L] = f_endLegY[L] - f_lastLegY[L]; //travel needed in local Y direction
            f_deltaZ[L] = f_endLegZ[L] - f_lastLegZ[L]; //travel needed in local Z direction
            sp2s("deltas: ",f_deltaX[L]); sp; sp2sl(f_deltaY[L],f_deltaZ[L]);
         } //for L=1...
      }  // else if f_active != 0
   } // if f_goodData
   return f_goodData;            // return, tellling called if we ran into problems

}                     
