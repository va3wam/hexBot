// This is the file flows.cpp, which lives in the include directory.
// and is invoked by an include statement in main.cpp
// routines here have corresponding entries in include/flows.h


#include <flows.h>               // including main.h
int8_t rgbLedClr = 0; //  Track what colour to set the rgb led to next when working on a new flow row.
void setupFlows()
{  // initialize params for the accumulation of flow rows from MQTT FLOW commands
   f_active = 0;      // what row number we fill next, and also the count of rows seen for current flow
                              // set up leg info that's indexable by leg number from 1 to 6

// GLOBAL coords for each leg's home position
// these are now dynamic, due to the fo_newHomexxx flow operations
// these 6 lines are re-executed in the fo_newHomeReset operation
   f_dynGHomeX[1] =  18.62 ; f_dynGHomeY[1] = -14.79 ; f_dynGHomeZ[1] = -10.60 ; 
   f_dynGHomeX[2] =   0    ; f_dynGHomeY[2] = -20.71 ; f_dynGHomeZ[2] = -10.60 ;
   f_dynGHomeX[3] = -18.62 ; f_dynGHomeY[3] = -14.79 ; f_dynGHomeZ[3] = -10.60 ;
   f_dynGHomeX[4] =  18.62 ; f_dynGHomeY[4] =  14.79 ; f_dynGHomeZ[4] = -10.60 ;
   f_dynGHomeX[5] =   0    ; f_dynGHomeY[5] =  20.71 ; f_dynGHomeZ[5] = -10.60 ;
   f_dynGHomeX[6] = -18.62 ; f_dynGHomeY[6] =  14.79 ; f_dynGHomeZ[6] = -10.60 ;

// perform a variety of per-leg initialization tasks

   for(int legnum=1; legnum<=6; legnum++) 
   {  f_dynLHomeX[legnum] = f_staticHomeX;   // initially, dynamic home is same as original home
      f_dynLHomeY[legnum] = f_staticHomeY;
      f_dynLHomeZ[legnum] = f_staticHomeZ;

      legIndexDriver[legnum] = (legnum - 1) / 3 ;        // 0 for left side, 1 for right side
      legIndexHipPin[legnum] = ((legnum -1) % 3 ) * 3;   // 0, 3, 6, 0, 3, 6
   }

// initialize the flow operation codes for translation of alpha mnemonics
// index numbers are determined by position in the mnemonic lookup string in mqttBroker flow command processing
// values are fo_operation codes, which are used in displatching by operation for short & long flow commands
   f_flowOps[ 1] = fo_moveGlobal;      //MGC    Move to Global Coordinates
   f_flowOps[ 2] = fo_moveLocal;       //MLC    Move to Local Coordinates
   f_flowOps[ 3] = fo_moveGRelHome;    //MGRH   Move using Global offsets Relative to Home
   f_flowOps[ 4] = fo_moveLRelHome;    //MLRH   Move using Local offsets Relative to Home
   f_flowOps[ 5] = fo_moveGRelLast;    //MGRL   Move using Global offsets Relative to Last
   f_flowOps[ 6] = fo_moveLRelLast;    //MLRL   Move using Local offsets Relative to Last
   f_flowOps[ 7] = fo_newHomeGCoords;  //NHGC   New Home using Global Coordinates
   f_flowOps[ 8] = fo_newHomeLCoords;  //NHLC   New Home using Local Coordinates
   f_flowOps[ 9] = fo_newHomeHere;     //NHH    New Home Here
   f_flowOps[10] = fo_newHomeReset;    //NHR    New Home Reset
   f_flowOps[11] = fo_continuePrevFlow;//CPF    Continue Previous Flow
   f_flowOps[12] = fo_markCycleStart;  //MCS    Mark Cycle Start
   f_flowOps[13] = fo_markCycleEnd;    //MCE    Mark Cycle End
   f_flowOps[14] = fo_doCycle;         //DC     Do Cycle
   f_flowOps[15] = fo_toeSafetyX;      //TSX    Toe Safety X limits
   f_flowOps[16] = fo_toeSafetyY;      //TSY    Toe Safety Y limits
   f_flowOps[17] = fo_toeSafetyX  ;    //TSZ    Toe Safety Z limits
   f_flowOps[18] = fo_toeSafetyReset;  //TSR    Toe Safety Reset

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

// initialize dynamic home position in local coords for each leg

} // void setupFlows()

/**
 * @brief Do configuration set up that is unique to each robot, including:
 * - define servo calibration offset values
 * called from setup() in main.cpp
 * tried to put this routine in hexBot/lib/aaWeb-1.0.0/lib/aaNetwork-main/src/aaNetwork.cpp
 *    but couldn't get it to work, due to object structure issues I suspect
 =============================================================================*/
 void setupPerBotConfig()     // do the robot-specific setup
 {
    String macAdd = WiFi.macAddress(); // Get MAC address as String
    sp2("<setupPerBotConfig> MAC Address: ", macAdd);  // see if we can read this variable
    if(macAdd == "3C:61:05:4A:DD:98")  // Doug's MAC address
    {
       sp1l("  Doing bot-specific setup for Doug's MAC address");
       // set up the servo calibration offsets
       // PWM value used = (PWM calculated from angle) + (calibration offset for this servo) - 299
       // note that servoOffset[0] is not used
       servoOffset[ 1] = 299;
       servoOffset[ 2] = 299;
       servoOffset[ 3] = 299;
       servoOffset[ 4] = 299;
       servoOffset[ 5] = 299;
       servoOffset[ 6] = 299;
       servoOffset[ 7] = 299;
       servoOffset[ 8] = 299;
       servoOffset[ 9] = 299;
       servoOffset[10] = 299;
       servoOffset[11] = 299;
       servoOffset[12] = 299;
       servoOffset[13] = 299;
       servoOffset[14] = 299;
       servoOffset[15] = 299;
       servoOffset[16] = 299;
       servoOffset[17] = 299;
       servoOffset[18] = 299;

    }
    else if(macAdd == "94:B9:7E:5F:4A:40")  // Andrew's MAC address
    {
       sp1l("  Doing bot-specific setup for Andrew's MAC address");
       // set up the servo calibration offsets
       // PWM value used = (PWM calculated from angle) + (calibration offset for this servo)
       // note that servoOffset[0] is not used
       servoOffset[ 1] = 299;
       servoOffset[ 2] = 299;
       servoOffset[ 3] = 299;
       servoOffset[ 4] = 299;
       servoOffset[ 5] = 299;
       servoOffset[ 6] = 299;
       servoOffset[ 7] = 299;
       servoOffset[ 8] = 299;
       servoOffset[ 9] = 299;
       servoOffset[10] = 299;
       servoOffset[11] = 299;
       servoOffset[12] = 299;
       servoOffset[13] = 299;
       servoOffset[14] = 299;
       servoOffset[15] = 299;
       servoOffset[16] = 299;
       servoOffset[17] = 299;
       servoOffset[18] = 299;
    }
    else    // neither MAC address matched
    {
       nl;
       sp2l("<setupPerBotConfig> Unrecognized MAC address. Per Bot configuration was bypassed", macAdd);
    }
 } // void setupPerBotConfig()

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
int32_t mapDegToPWM(float degrees, int servo)
{
   // degrees is the desired angle, between -90 and +90 degrees
   // servo is the servo number (1 - 18) used for software position calibration table lookup
   const float offset = 90; // max allowed deviation from center position
   // if max offset is exceeded, the fixup variable corrects it to edge of range
   // TODO #26 create constants for all magic numbers in this function. 
   // range check the desired degrees value
   float fixup = 0;       // initially, assume degrees is within range defined by offset
   if(degrees < - offset)  { fixup = offset - degrees; } 
   if(degrees >   offset)  { fixup = offset - degrees; }
   // formula fits a line to two measured data points (x=degrees, y=PWM) with 
   // the points selected to minimize overall errors: (24,160) (166,460)
   // formula is based on y = M * x + b where M is the slope, 
   // (delta Y)/(delta X) for 2 selected points, b is the y intercept, derived 
   // by substituting a selected point into above formula after slope is known.
   // servoOffset[] is a fine tuning software adjustment, per servo, of the servo center pwm value
   //   it's initialized in the robot specific startup code in setupPerBotConfig() just above
   int adjust = 299;                // center is 299 if no specific servo is given
   if(servo != 0)                   // if a servo number was given
   {
      adjust = servoOffset[servo];  // look up its software corrected center
   }
   return (degrees - (fixup - offset)) * 300 / 142 + 109.3 + (adjust - 299) ;
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
   // todo #93
   *toeX = (BT + BS * cos(radians(-knee)) + BF *sin(radians(ankle - knee + BTOA))) * cos(radians(hip));
   *toeY = -BS * sin(radians(knee)) - BF * cos(radians(ankle - knee + BTOA));
   *toeZ = sin(radians(hip)) * ( BT + BS * cos(radians(-knee)) + BF * sin(radians(ankle - knee + BTOA) ) );
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

   // hexbot body measurements, copied from flows.h for convenience
   // const float BT = 2.915 ;   // thigh length (between hip and knee, horizontally)
   // const float BS = 7.620 ;   // shin length (between knee and ankle)
   // const float BF = 11.059;   // foot length (diagonal between ankle and toe)
   // const float BTOA = 17.063; // toe offset angle = angle between ankle servo vertical, and toe, in degrees
   // const float BTOD = 3.245;  // toe offset distance. perpendicular distance from toe to ankle servo vertical line

   f_angH = degrees( atan2(Tz, Tx) ) ;       // the hip angle is the easy one.

   // now reduce to a 2D problem by rotating leg into xy plane (around y axis)
   Ux = Tx * cos(radians(- f_angH)) - Tz * sin(radians(- f_angH));
   Uy = Ty; // the rotation doesn't change the y value
   // documentation explains the use of 2 coefficients to simplify the algebra
   C1 = BS * BS - BF * BF + Ux * Ux + Uy * Uy - BT * BT ;
   C2 = 2 * BT - 2 * Ux ;
   // the equations of 2 intersecting circles reduces to a quadratic equation for Ax
   // calculate the quadratic coefficients for A*x^2 + B*x +c = 0
   QA = 1 + (C2 * C2) / (4 * Uy * Uy) ;
   QB = (-2 * BT) + (2 * C1 * C2) / (4 * Uy * Uy);
   QC = BT * BT + (C1 * C1) / (4 * Uy * Uy) - BS * BS;
   // The x quadratic solution is the ankle's x coordinate, and will be referred to as Ax
   // We'll optimistically use the plus case choice for the "plus or minus" in the quadratic solution...
   //   x = (-B +/- SQRT( B*B - 4 * A * C) / (2 * A)
   DET = round(( QB * QB - 4 * QA * QC) * 10000) / 10000 ;  //if roundoff error causes a tiny -Ve #, SQRT barfs
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
    // and the effect of knee movement on foot angle
    f_angA = degrees( atan2( Ux - Ax, Ay - Uy)) - BTOA + f_angK ;
   
} // coordsToAngles()


bool globCoordsToLocal(int legNumber, float gx, float gy, float gz)
{
// local coordinates are returned in f_endLegX[legnumber], f_endLegY[legnumber], and f_endLegZ[legnumber]
// leg numbers: 1=FrontRight, 2=MR, 3=BR, 4=FrontLeft, 5=ML, 6=BL

// rotating a vector(X,Y) thru counter clockwise angle B, to get (Xr,Yr)
//    Xr = cos(B) * X - sin(B) * Y
//    Yr = sin(B) * X + cos(B) * Y

   float Xrt, Yrt ;  //temp variables for rotated global X & Y coords

   f_endLegY[L] = gz;       // height above robot is global Z, local Y
   switch (legNumber) 
   {
      case 1:
        // Front Right leg
        Xrt = cos_m45 * (gx-fp_frontHipX) - sin_m45 * (gy + fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_m45 * (gx-fp_frontHipX) + cos_m45 * (gy + fp_frontHipY);
        f_endLegX[legNumber] = -1 * Yrt;
        f_endLegZ[legNumber] = Xrt;
        break;
      case 2:
        // Middle Right leg
        f_endLegX[legNumber] = -1 * gy - fp_sideHipY;
        f_endLegZ[legNumber] = gx;
        break;
      case 3:
        // Back Right leg
        Xrt = cos_p45 * (gx + fp_frontHipX) - sin_p45 * (gy + fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_p45 * (gx + fp_frontHipX) + cos_p45 * (gy + fp_frontHipY);
        f_endLegX[legNumber] = -1 * Yrt;
        f_endLegZ[legNumber] = Xrt;        
        break;
      case 4:
        // Front Left leg
        Xrt = cos_p45 * (gx - fp_frontHipX) - sin_p45 * (gy - fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_p45 * (gx - fp_frontHipX) + cos_p45 * (gy - fp_frontHipY);
        f_endLegX[legNumber] = Yrt;
        f_endLegZ[legNumber] = -1 * Xrt;         
        break;
      case 5:  
        // Middle Left leg
        f_endLegX[legNumber] = gy - fp_sideHipY;
        f_endLegZ[legNumber] = -1 * gx ;
        break;
      case 6:
        // Back Left leg
        Xrt = cos_m45 * (gx - (-fp_frontHipX)) - sin_m45 * (gy - fp_frontHipY);  // rotated (Xg,Yg)
        Yrt = sin_m45 * (gx - (-fp_frontHipX)) + cos_m45 * (gy - fp_frontHipY);
        f_endLegX[legNumber] = Yrt;
        f_endLegZ[legNumber] = -1* Xrt;        
        break;
      default:
        return false;
   }
   return true;
}

void localCoordsToGlobal(int legNumber, float lx, float ly, float lz)
{  // answers (global x,y,z) are returned in f_graphX, f_graphY, and f_graphZ
   f_graphZ = ly;    //height off floor
   switch (legNumber) 
   {
      case 1:
        // Front Right leg
        f_graphX = f_hipX[legNumber] + lx * cos_p45 + lz * cos_p45;
        f_graphY = f_hipY[legNumber] - lx * cos_p45 + lz * cos_p45;
        break;
      case 2:
        // Middle Right leg
        f_graphX = f_hipX[legNumber] + lz;
        f_graphY = f_hipY[legNumber] - lx;
        break;
      case 3:
        // Back Right leg
        f_graphX = f_hipX[legNumber] - lx * cos_p45 + lz * cos_p45;
        f_graphY = f_hipY[legNumber] - lx * cos_p45 - lz * cos_p45;
        break;
      case 4:
        // Front Left leg
        f_graphX = f_hipX[legNumber] + lx * cos_p45 - lz * cos_p45;
        f_graphY = f_hipY[legNumber] + lx * cos_p45 + lz * cos_p45;
        break;
      case 5:
        // Middle Left leg
        f_graphX = f_hipX[legNumber] - lz;
        f_graphY = f_hipY[legNumber] + lx;
        break;
      case 6:
        // Back Left leg
        f_graphX = f_hipX[legNumber] - lx * cos_p45 - lz * cos_p45;
        f_graphY = f_hipY[legNumber] + lx * cos_p45 - lz * cos_p45;
        break;
      default:
         break;
   }
   //sp4sl("legnum,lx,f_graphY",legNumber,lx,f_graphY);
   return;

}

// do_flow is enabled by the MQTT flow_go command, which sets f_flowing to true
// f_flowing is checked in loop() and calls do_flow() on every loop, if it's enabled
// f_active is initially zero, which initiates various setup activities on first do_flow entry
// in general case, do_flow executes a small servo movement on all 18 servos, at a calculated time interval

void do_flow()          // called from loop if there's a flow executing that needs attention
{
   float t_angK, t_angA, t_angH; // temp angles used in PWM calculations for oppositely mounted servos
   if(f_active == 0)             // starting a new flow, so need to do some setup
   {
      sp1l(" start of flow row # 0");
// do conditional display of entire flow here, nicely formatted, with row numbering
      if((toeMoveAction & fa_dispFlow) != 0)    // if requested in the FG command at the end of the script
      {  // display the entire flow, nicely formatted, with row numbers
         for(int r=0; r<f_count; r++)  // step through the flow rows
         {  // most flow rows are long, except the control ones for cycles, new home positions, toe safety set up, etc which lack the 18 trailing numbers
            if(f_operation[r] >= fo_markCycleStart && f_operation[r] <= fo_doCycle )   // if it's a short flow row...
            {  printf("%02d)%4d %2d %2d %6.2f %6.2f %6.2f\n",r,f_msecs[r],f_operation[r],f_lShape1[r],f_lShape2[r],f_lShape3[r],f_lShape4[r]);
            }
            else
            {  printf("%02d)%4d %2d %2d %6.2f %6.2f %6.2f  %6.2f %6.2f %6.2f/%6.2f %6.2f %6.2f/%6.2f %6.2f %6.2f/%6.2f %6.2f %6.2f/%6.2f %6.2f %6.2f/%6.2f %6.2f %6.2f\n",
               r,f_msecs[r],f_operation[r],f_lShape1[r],f_lShape2[r],f_lShape3[r],f_lShape4[r],
               f_legX[r] [1], f_legY[r] [1], f_legZ[r] [1],
               f_legX[r] [2], f_legY[r] [2], f_legZ[r] [2],
               f_legX[r] [3], f_legY[r] [3], f_legZ[r] [3],
               f_legX[r] [4], f_legY[r] [4], f_legZ[r] [4],
               f_legX[r] [5], f_legY[r] [5], f_legZ[r] [5],
               f_legX[r] [6], f_legY[r] [6], f_legZ[r] [6] );
            }
         }
      }
      // last flow might have changed the home position. start this new flow with the default home position
      handle_fo_newHomeLReset();
      f_active = 0;     // undo the change to f_active that the home reset does
      
      // we're going to need local coords to be able to figure angles, then the PWM commands to feed to servos
      // the operation code in f_operation[f_active] tells us what kind of coords we were given
      f_goodData = true;               // assume thing will go well, & f_operation is valid
      prepNextLine();         // get local coords of position in active flow row in f_endlegX[L], Y, Z

      if(f_goodData)
      {  // f_endLegX[leg],Y,Z arrays contain the local coords of the position we need to jump to
   //  for(L=1; L<=6; L++)
         for(int l_base=1;l_base<=3;l_base++)   // use alternate sides for leg movements, resting PWM drivers
         {  for(L=l_base;L<=l_base+3;L=L+3)     // i.e. 1, 4, 2, 5, 3, 6         
            {  // move each leg to the position in local coords in f_endLegX[l], f_endLegY[l], f_endLegZ[l]
               // the call that actually moves servo is pwmDriver[driver].setPWM[pin, pwmClkStart, pwm-value]
               //   the driver we can lookup in legIndexDriver[leg]
               //   the pin can be derived from legIndexHipPin[leg]
               //   to get pwm value, we convert local coords to angles, then from angles to pwm values
               coordsToAngles(f_endLegX[L], f_endLegY[L], f_endLegZ[L]); 
   //            Log.noticeln("<do_flow> Leg %u, angH = %F, angK = %F, angA = %F",L,f_angH,f_angK,f_angA);
               f_lastAngH[L] = f_angH;       // remember angles so we can skip redundant moves in future
               f_lastAngK[L] = f_angK;
               f_lastAngA[L] = f_angA;

               // now, one servo wihin the leg at a time, figure the pwm value, and move the servo
               // might have to temporarily negate angles, due to opposite servo mounting on either side of bot
               t_angH = f_angH;    // may need to negate this angle for PWM calculation purposes, depending on leg
               t_angK = f_angK;
               t_angA = f_angA;
               if(L >= 4)
               {  // t_angH = -1 * t_angH;   // need to use -ve angles for PWM calculation purposes on one side of bot,
                  t_angK = -1 * t_angK;   //... because servos are mounted opposite ways on opposite sides of bot
                  t_angA = -1 * t_angA;
               }  // if L>=4


               // starting with the hip...
   //            int legstart = micros();  // timestamp start of leg movement
               servoNum = ((L - 1) * 3) +1;   // servo numbers go from 1 to 10. This is hip servo for leg L
               pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L],  pwmClkStart, mapDegToPWM(t_angH,servoNum));
   //            Log.noticeln("H: Driver=%d,  Pin=%d, angH=%F,  pwm=%d",legIndexDriver[L],legIndexHipPin[L],f_angH, mapDegToPWM(f_angH,0));
               servoNum = ((L - 1) * 3) +2;   // servo numbers go from 1 to 10. This is knee servo for leg L
               pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+1,pwmClkStart, mapDegToPWM(t_angK,servoNum));
   //            Log.noticeln("K: Driver=%d,  Pin=%d, angH=%F,  pwm=%d",legIndexDriver[L],legIndexHipPin[L]+1,f_angK, mapDegToPWM(f_angK,0));
               servoNum = ((L - 1) * 3) +3;   // servo numbers go from 1 to 10. This is ankle servo for leg L
               pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+2,pwmClkStart, mapDegToPWM(t_angA,servoNum));
   //            Log.noticeln("A: Driver=%d,  Pin=%d, angH=%F,  pwm=%d",legIndexDriver[L],legIndexHipPin[L]+2,f_angA, mapDegToPWM(f_angA,0));
               f_lastLegX[L] = f_endLegX[L];   // remember this initial location as start of next line
               f_lastLegY[L] = f_endLegY[L];
               f_lastLegZ[L] = f_endLegZ[L];
               // ok, the 3 servos in that leg have been moved - on to the next leg
            }  // for(L=l_base;L<=l_base+3;L=L+3) 
         } // for(int l_base=1;l_base<=3;l_base++) 
         //at this point, all legs have been moved to the initial position in the flow
         // well, move commands have been sent. pause a bit for the servos to actually move
         delay(340);             // in theory, wost case is about 120 degrees, & servo does 60 degrees in .17 sec
         // start preparing for frame by frame moves from this positon to next one in flow, i.e. [1] in flow rows
         // first, figure out local coords of that next position, like we did for initial position
         if(f_count > 1 )     // is there at least one more flow row?
         {                    // yup - set up to do frames to get to it
 
            // we need local coords to be able to give commands to servos
            // the operation code in f_operation[f_active] tells us what king of coords we were given
            f_active=1;             // OK, we're now processing flow row 1 for first real line
            prepNextLine();         // decode flow row 1's position, figure deltas, etc
                                    // so we'll be ready at next 20 ms mark
            f_frame = 1 ;           // initialize frame counter
            f_framesPerPosn = int((f_msecs[1] / f_msecPerFrame) + .5);  // rounded count of how many frames fit in time)
            sp1l(" start of flow row # 1");
            if((toeMoveAction & fa_graphPrint) != 0) { sp1s(f_active);} // keep output for Calc graphing uniform
         } // if f_count > 1
         else  // if f_count > 1. else case  means only initial position was given in flow
         {  f_flowing = false;      // stop flow processing
            sp1l(" end of single row flow processing");
         }
      }  // if(goodData)
      else   // f_goodData was false - abort flow
      {    f_flowing = false;         // stop executing the flow
      }
      
   } // if f_active == 0

   // OK above takes care of initial case for initial flow row where flow is just starting
   // now the work of grinding out the servo changes for everu 20 msec frame, fo 6 legs
   else if( f_active > 0)
   {  if(millis() >= f_nextTime)          // did we get to next 20 msec frame time?
      {                                   // we did hit 20 ms mark - time to move servos
                                          // (otherwise exit immediately & wait)
// bool DF = false;
// if((f_active>0) & (f_active<3)) {DF=true;}   // debug flag for reducing test output in loops

         f_nextTime = millis() + f_msecPerFrame;    // yup, quickly reset for next 20 msec interval
         for(int l_base=1;l_base<=3;l_base++)   // use alternate sides for leg movements, resting PWM drivers
         {  for(L=l_base;L<=l_base+3;L=L+3)     // i.e. 1, 4, 2, 5, 3, 6         
            {                                   // use frame count to figure next frame position
               f_tmpX = (float)f_frame * f_deltaX[L] / (float)f_framesPerPosn + f_lastLegX[L];
               f_tmpY = (float)f_frame * f_deltaY[L] / (float)f_framesPerPosn + f_lastLegY[L];
               f_tmpZ = (float)f_frame * f_deltaZ[L] / (float)f_framesPerPosn + f_lastLegZ[L];
               coordsToAngles(f_tmpX, f_tmpY, f_tmpZ); // creates f_angH, f_angK, f_angAltaZ[L]);}
               // now, one servo within the leg at a time, figure the pwm value, and move the servo
               // might have to temporarily negate angles, due servos mounted opposite on either side of bot
               t_angK = f_angK;    // may need to negate this angle for PWM calculation purposes, depending on leg
               t_angA = f_angA;
               t_angH = f_angH;

               if(L >= 4)
               {  t_angK = -1 * t_angK;   // need to use -ve angles for PWM calculation purposes on one side of bot,
                  t_angA = -1 * t_angA;   //... because servos are mounted opposite ways on opposite sides of bot
                  // t_angH = -1 * t_angH;   
               }  // if L>=4

               // starting with the hip...
               if((toeMoveAction & fa_moveServos) != 0)    // did flow_go command options tell us to move servos?
               {  if(f_angH != f_lastAngH[L])               // if new hip angle is different than last one, move the servo 
                  {  
                     servoNum = ((L - 1) * 3) +1;   // servo numbers go from 1 to 18. This is hip servo for leg L
                     pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L],  pwmClkStart, mapDegToPWM(t_angH,servoNum));
                     f_lastAngH[L] = f_angH;                // and update last angle for this servo
                  }
               }
               if((toeMoveAction & fa_moveServos) != 0)    // did flow_go command options tell us to move servos?
               {  if(f_angK != f_lastAngK[L])               // only if the knee angle has changed...
                  {  
                     servoNum = ((L - 1) * 3) +2;   // servo numbers go from 1 to 18. This is knee servo for leg L
                     pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+1,pwmClkStart, mapDegToPWM(t_angK,servoNum));
                     f_lastAngK[L] = f_angK;
                  }
               }
               if((toeMoveAction & fa_moveServos) != 0)    // did flow_go command options tell us to move servos?
               {  if(f_angA != f_lastAngA[L])               // only if ankle angle has changed...
                  {  
                     servoNum = ((L - 1) * 3) +3;   // servo numbers go from 1 to 18. This is ankle servo for leg L
                     pwmDriver[legIndexDriver[L]].setPWM(legIndexHipPin[L]+2,pwmClkStart, mapDegToPWM(t_angA,servoNum));
                     f_lastAngA[L] = f_angA;
                  }
               }
               if((toeMoveAction & fa_dispPWM) != 0)    // if flow go command options told us to display PWM..
               {  
                  servoNum = ((L - 1) * 3) +1;   // servo numbers go from 1 to 18. This is hip servo for leg L 
                  sp2s(mapDegToPWM(t_angH,servoNum),mapDegToPWM(t_angK,servoNum+1));sp1s(mapDegToPWM(t_angA,servoNum+2)); 
               }
               if((toeMoveAction & fa_dispAngles) != 0) // if flow_go command options told us to display angles..
               {  sp2s(t_angH,t_angK);  sp1s(t_angA); 
               }
               if((toeMoveAction & fa_dispLocal) != 0) // if flow_go command options told us to display local coords..
               {  sp2s(f_tmpX,f_tmpY);  sp1s(f_tmpZ);  
               }
               if((toeMoveAction & fa_graphPrint) != 0) // if flow_go command options told us to display local coords..
               {  localCoordsToGlobal(L, f_tmpX, f_tmpY, f_tmpZ);   // convert local to global coords, into f_graphX...
                  sp2s(f_graphX,f_graphY);  // print global coords suitable for Calc graphing
               }
            }  //for L=l_base...
         } // for l_base = 1...
         // output gets messy if you display more than one attribute at a time - avoid that
         if((toeMoveAction & (fa_dispPWM + fa_dispAngles + fa_dispLocal + fa_graphPrint)) != 0)  // if we displayed numbers
         {  nl;                              // then output the final new line
         }
         f_frame ++  ;                          // advance to next frame within the flow row
         if(f_frame > f_framesPerPosn)          // did we run out of frames?
         {  // yup - we must be sitting at end position of the line, otherwise wait for next 20 msec
            f_active = f_active + 1 ;                       // advance to next flow row
            if(f_active < f_count)              // have we run out of flow rows to do?
            {  // there are rows left, f_active points to a valid flow row
               if((toeMoveAction & fa_graphPrint) == 0)  // if we're NOT doing Calc compatible output...
               { sp2sl(" start of flow row #",f_active);   // announce start of this flow row 
               }
               for(L=1; L<=6; L++)              // remember end of last line as start of next one
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
               sp1l(" end of multi row flow processing");
            }
         } // if(f_frame > f_framesPerPosn) 
         if((toeMoveAction & fa_graphPrint) != 0) {sp1s(f_active); }  // put flow row # at start of Calc fa_graphPrint lines
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

{
   prepNextLine1() ;        // look at next line, which could be a control command
   if(didControl)          // it was a control command, so redo prepNextLine to get movement command
   {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow-row #",f_active); }
      // note dash in "flow-row" in above message 
      prepNextLine1();     // could have 2 control commands in a row.
      if(didControl)
      {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow~row #",f_active);} 
         // note tilde in "flow~row" in above message
         prepNextLine1();         
         if(didControl)
         {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow~row #",f_active);} 
            // note tilde in "flow~row" in above message
            prepNextLine1();         
            if(didControl)
            {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow~row #",f_active);} 
               // note tilde in "flow~row" in above message
               prepNextLine1();         
               if(didControl)
               {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow~row #",f_active);} 
                  // note tilde in "flow~row" in above message
                  prepNextLine1();         
                  if(didControl)
                  {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow~row #",f_active);} 
                     // note tilde in "flow~row" in above message
                     prepNextLine1();         
                     if(didControl)
                     {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow~row #",f_active);} 
                        // note tilde in "flow~row" in above message
                        prepNextLine1();         
                        if(didControl)
                        {  if((toeMoveAction & fa_graphPrint) == 0) { sp2sl(" start of flow~row #",f_active);} 
                           // note tilde in "flow~row" in above message
                           prepNextLine1();         
                           if(didControl) { sp2sl(" **** unhandled 9 consecutive control commands around flow row: ",f_active)}
                        } // if(didControl)
                     } // if(didControl)
                  } // if(didControl)
               } // if(didControl)
            } // if(didControl)
         } // if(didControl)
      } // if(didControl)
   }  // if(didControl)    // really should make this structure a loop
   return true;
}
//          if(didControl) { sp2sl(" **** unhandled 3 consecutive control commands around flow row: ",f_active)}

// bool prepNextLine1()  - // set up for toes movements according to next line in flow row

     // return true if we saw a control command and still need to set up for movement
     // return false if we saw a move command, and not a control command command
// prepare for next movement line that goes from position in last flow row to one in current flow row
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

bool prepNextLine1()          

{ 
  // initialize to start doing frame by frame moves in the line between
   // previous flow row's position: lastLegX[L], Y, Z, and
   // this flow row's (identified by f_active) position: f_legX[f_active][L], Y, Z
   // local coords of end point of line are left in f_endLegX[L], Y, Z
   // f_operation in flow row tells us what kind of numbers are given for each leg

   f_goodData = true;   // initially assume all will go well
   didControl = false;  // ...and that we'll do a leg movement command, not a control command
   rgbLedClr ++; // Increment rgb colour to use next.
   if(rgbLedClr > numColoursSupported) // Never exceed known colour numbers
   {
      rgbLedClr = 0;
   } // if
   // following line removed because it causes console messages in the middle of spreadsheet data
   // setStdRgbColour(rgbLedClr); // Set RGB led colour
   if      (f_operation[f_active] == fo_moveGlobal)         {handle_fo_moveGlobal();} 
   else if (f_operation[f_active] == fo_moveLocal)       {handle_fo_moveLocal();} 
   else if (f_operation[f_active] == fo_moveGRelHome)    {handle_fo_moveGRelHome();}
   else if (f_operation[f_active] == fo_moveLRelHome)    {handle_fo_moveLRelHome();}

   else if (f_operation[f_active] == fo_moveGRelLast)    {handle_fo_moveGRelLast();} 
   else if (f_operation[f_active] == fo_moveLRelLast)    {handle_fo_moveLRelLast();}    // FO_moveGRelLast and fo_moveLRelLast, moving relative to last position, aren't implemented yet

   else if (f_operation[f_active] == fo_newHomeGCoords)  {handle_fo_newHomeGCoords();}
   else if (f_operation[f_active] == fo_newHomeLCoords)  {handle_fo_newHomeLCoords();}
   else if (f_operation[f_active] == fo_newHomeHere)     {handle_fo_newHomeHere();}
   else if (f_operation[f_active] == fo_newHomeReset)    {handle_fo_newHomeLReset();}
   //else if (f_operation[f_active] == fo_ContinuePrev)    {handle_fo_ContinuePrev();}

   else if (f_operation[f_active] == fo_markCycleStart ) {handle_fo_markCycleStart();}
   else if (f_operation[f_active] == fo_markCycleEnd )   {handle_fo_markCycleEnd();}
   else if (f_operation[f_active] == fo_doCycle)         {handle_fo_doCycle();}

   else if (f_operation[f_active] == fo_toeSafetyX)      {handle_fo_toeSafetyX();}
   else if (f_operation[f_active] == fo_toeSafetyY)      {handle_fo_toeSafetyY();}
   else if (f_operation[f_active] == fo_toeSafetyZ)      {handle_fo_toeSafetyZ();}
   else if (f_operation[f_active] == fo_toeSafetyReset)  {handle_fo_toeSafetyReset();}


   else
   {  // unsupported op code in nextfirst row - abort
      f_flowing = false;         // stop executing the flow
      f_cycling = false;         // abort repeatable cycle, if we were in one
      f_goodData = false;        // bypass rest of do_flow processing
      // need to avoid falling into following code. use a flag for "good data seen" ?
   }
   if(f_goodData)       // continue only if we haven't aborted due to an error, 
                        // and didn't do a control command that already returned
   {
      // get here if we've been able to calculate local coordinates for next toe position
      // now we need to see if requested position is within "safe positions box"

      String badLegs = "" ;   // initialize error message identifying unsafe positions
      for(L=1; L<=6; L++ )       // go thru all legs
      { 
//sp2s(f_endLegX[L],f_endLegY[L]); sp; sp1l(f_endLegZ[L]);
         if(f_endLegX[L] - f_staticHomeX > safeMaxPosX){badLegs =badLegs +legNum[L] +"XP ";
            sp5sl(L,"XP:home,new,max=",f_staticHomeX,f_endLegX[L],safeMaxPosX);}
         if(f_staticHomeX - f_endLegX[L] > safeMaxNegX){badLegs =badLegs +legNum[L] +"XN ";
            sp5sl(L,"XN:home,new,max=",f_staticHomeX,f_endLegX[L],safeMaxNegX);}
         if(f_endLegY[L] - f_staticHomeY > safeMaxPosY){badLegs =badLegs +legNum[L] +"YP ";
            sp5sl(L,"YP:home,new,max=",f_staticHomeY,f_endLegY[L],safeMaxPosY);}
         if(f_staticHomeY - f_endLegY[L] > safeMaxNegY){badLegs =badLegs +legNum[L] +"YN ";
            sp5sl(L,"YN:home,new,max=",f_staticHomeY,f_endLegY[L],safeMaxNegY);}
         if(f_endLegZ[L] - f_staticHomeZ > safeMaxPosZ){badLegs =badLegs +legNum[L] +"ZP ";
            sp5sl(L,"ZP:home,new,max=",f_staticHomeZ,f_endLegZ[L],safeMaxPosZ);}
         if(f_staticHomeZ - f_endLegZ[L] > safeMaxNegZ){badLegs =badLegs +legNum[L] +"ZN ";
            sp5sl(L,"ZN:home,new,max=",f_staticHomeZ,f_endLegZ[L],safeMaxNegZ);}
      }  // for L=1...
      if(badLegs != "")             // if any safety violation ocurred..
      {  f_goodData = false;        // abort further processing of the flow row
         f_flowing = false;         // and stop fow processing
         sp2l("****************** toe safety violation(s) [<leg><coord><positive or negative side> : ",badLegs);
         for(int j=1;j<=6;j++)
         {  sp3s("active, Lax,Lay,Laz",f_active,f_endLegX[j]);sp2sl(f_endLegY[j],f_endLegZ[j]);
         }
      } // if badLegs != ""
      else if(f_active != 0)     // first flow is special case with direct jump rather than frames
      {  // figure deltas for end points on movement lines for each leg, for each axis
         for(int L=1; L<=6; L++)   // L stands for leg. short to avoid cobol expression syndrome
         {  f_deltaX[L] = f_endLegX[L] - f_lastLegX[L]; //travel needed in local X direction
            f_deltaY[L] = f_endLegY[L] - f_lastLegY[L]; //travel needed in local Y direction
            f_deltaZ[L] = f_endLegZ[L] - f_lastLegZ[L]; //travel needed in local Z direction
            f_frame = 1;                     // new sequence of frames for next flow row
            f_framesPerPosn = int((f_msecs[f_active] / f_msecPerFrame) + .5);  // rounded count of how many frames fit in time
         } //for L=1...
      }  // else if f_active != 0
   } // if f_goodData
   return false;            // return, telling caller there's no need for an encore call due to cycle command
} 

// ======== handler routines for the various f_operation codes in flow commands =========

void handle_fo_moveGlobal()
{  // we were given absolute coords, and need to convert to local coords
   for(L=1; L<=6; L++)   // l stands for leg. short to avoid cobol expression syndrome
   {  globCoordsToLocal(L,f_legX[f_active][L],f_legY[f_active][L],f_legZ[f_active][L]);   // local coords returned in f_endLegX[L],...
   }
} // handle_fo_moveAbs()

void handle_fo_moveLocal()   // does flow row contain local cords?
{  // yup, we were given the local coordinate that we need, so just copy them
   for(L=1; L<=6; L++) 
   {  f_endLegX[L] = f_legX[f_active][L];   // get local coords right out of flow row
      f_endLegY[L] = f_legY[f_active][L];
      f_endLegZ[L] = f_legZ[f_active][L];
   }
} // void handle_fo_moveLocal()


void handle_fo_moveGRelHome()
{  // we were given offsets relative to home position, expressed in GLOBAL coords, so add in home coords
   for(L=1; L<=6; L++)  // add offset to home's global coord, to get final global coord
   {  f_tmpX = f_legX[f_active][L] + f_dynGHomeX[L];   
      f_tmpY = f_legY[f_active][L] + f_dynGHomeY[L];
      f_tmpZ = f_legZ[f_active][L] + f_dynGHomeZ[L];
      // then convert global coords to local coords
      globCoordsToLocal(L,f_tmpX,f_tmpY,f_tmpZ);   // local coords returned in f_endLegX[L],...
   }
} // void handle_fo_moveGRelHome() 

void handle_fo_moveLRelHome()
{  // we were given offsets relative to leg's home position, expressed in LOCAL coordinates
   for(L=1; L<=6; L++)
   {  f_endLegX[L] = f_legX[f_active][L] + f_dynLHomeX[L];   // get local offset out of flow row, and add to local home coords
      f_endLegY[L] = f_legY[f_active][L] + f_dynLHomeY[L];
      f_endLegZ[L] = f_legZ[f_active][L] + f_dynLHomeZ[L];
   }  
} // void handle_fo_moveLRelHome()

void handle_fo_moveGRelLast()
{  // we were given offsets in global coords from the last toe positions
// translate current location to global coords
   for(L=1; L<=6; L++)
   {  // translate current position to global coords
      localCoordsToGlobal(L, f_lastLegX[L], f_lastLegY[L], f_lastLegZ[L]);   // convert local to global coords, into f_graphX...
      // add offsets from flow command
      f_graphX += f_legX[f_active][L];
      f_graphY += f_legY[f_active][L];
      f_graphZ += f_legZ[f_active][L];
      // then translate back into local coords
      globCoordsToLocal(L,f_graphX,f_graphY,f_graphZ);   // local coords returned in f_endLegX[L],...
   }
} // handle_fo_moveGRelLast()

void handle_fo_moveLRelLast()
{  // we were given offsets in local coords from the last toe positions
   for(L=1; L<=6; L++)
   {  f_endLegX[L] = f_legX[f_active][L] + f_lastLegX[L];   // get local offset out of flow row, and add to current position
      f_endLegY[L] = f_legY[f_active][L] + f_lastLegY[L];
      f_endLegZ[L] = f_legZ[f_active][L] + f_lastLegZ[L];
   }  
} // handle_fo_moveLRelLast()

void handle_fo_markCycleStart()
{  // this flow row is a marker flagging the start of a repeatable cycle. param1 is the cycle #
   f_cycle = f_lShape1[f_active];  // get cycle identifier from flow row
   if(f_cycle < 0 || f_cycle > 10) { f_cycle = 0;}  // force out of bounds cycle # to a safe one
   f_cycleStart[f_cycle] = f_active + 1;     // remember that this cycle starts at the next flow row
   f_active ++ ;           // advance to flow row after the one with the markCycleStart operation code
   didControl = true;      // signal that we did a control command rather than preparing leg moves
   return;
} // void handle_fo_markCycleStart()

void handle_fo_markCycleEnd()
{  // this flow row is a marker flagging the end of a repeatable cycle. param1 is the cycle # 
   f_cycle = f_lShape1[f_active];  // get cycle identifier from flow row
   if(f_cycle < 0 || f_cycle > 10) { f_cycle = 0;}  // force out of bounds cycle # to a safe one
   f_cycleEnd[f_cycle] = f_active - 1;     // remember that this cycle ends at the previous flow row
   // not sure we need to track f_cycleEnd, since we run in to the end marker anyway.
   if(!f_cycling)    // are we currently executing a repeating cycle?     
   {   // if we're not in a cycle, we're just executing it once, & carrying on
      f_active ++ ;                 // advance to flow row after the one with the markCycleStart operation code
      didControl = true;            // signal that we did a control command rather than preparing leg moves
      return;
   }
   else
   {  // if we are cycling, then we've just completed one more repetition of the cycle
      if(f_cyclesLeft-- > 0)        //decrement repetition counter & check it
      {  // there are still more reps to do
         f_active = f_cycleStart[f_cycle];     // we want to continue at the beginning of the cycle
         didControl = true;         // signal that we did a control command rather than preparing leg moves
         return ;                   // signal the need for another call to set up for next movements
      }
      else  // there weren't any reps left for repeated cycle
      {  f_cycling = false;         //we're not running a cycle repetition anymore
         f_active = f_resumeRow;    // continue just after the flow row that requested the cycle
         didControl = true;         // signal that we did a control command rather than preparing leg moves
         return ;                   // signal the need for another call to set up for next movements
      } 
   }  
} // void handle_fo_markCycleEnd()

void handle_fo_doCycle()
{  //  the flow row is a marker telling robot to execute the repeatable cycle whose number is in param 1
   f_cycle = f_lShape1[f_active];         // get cycle identifier from flow row
   if(f_cycle < 0 || f_cycle > 10) { f_cycle = 0;}  // force out of bounds cycle # to a safe one
   f_cyclesLeft = f_lShape2[f_active];    // second parameter is repetition count for the cycle
   f_resumeRow = f_active + 1;            // what flow row to resume flow processing at after the repeated cycle is done
   f_active = f_cycleStart[f_cycle];      // next flow row to execute is start of cycle
   f_cycling = true;                      // note that we are in a repeating cycle.
   didControl = true;                     // signal that we did a control command rather than preparing leg moves
   return;                                // have to re-call ProcNextLine1 for new active flow row
} // void handle_fo_doCycle()

void handle_fo_newHomeGCoords()
{  // the 18 numbers in the arguments are the new GLOBAL coordinates of the home position
   // MQTT command processing put them into the flow arrays f_legX[f_active][L] ...

   for(L=1; L<=6; L++)           // for all the legs
   {
      f_dynGHomeX[L] = f_legX[f_active] [L];   // new dynamic home local coord is right out of flow command
      f_dynGHomeY[L] = f_legY[f_active] [L];
      f_dynGHomeZ[L] = f_legZ[f_active] [L];

      // we'll need to convert global coords to get equivalent local coords
      // first, save the f_endLegX[L]... values used to return answers - might need to conserve them
      float GTL_X = f_endLegX[L];
      float GTL_Y = f_endLegY[L];
      float GTL_Z = f_endLegZ[L];
      
      globCoordsToLocal(L,f_dynGHomeX[L],f_dynGHomeY[L],f_dynGHomeZ[L]);
      // local coordinates are returned in f_endLegX[legnumber],...
      f_dynLHomeX[L] = f_endLegX[L];
      f_dynLHomeY[L] = f_endLegY[L];
      f_dynLHomeZ[L] = f_endLegZ[L];
      // and restore original values for f_endLegX[L]...
      f_endLegX[L] = GTL_X;
      f_endLegY[L] = GTL_Y;
      f_endLegZ[L] = GTL_Z;
   } // for(L=1; L<=6; L++)  
   f_active ++ ;                 // advance to flow row after the one with this control operation code
   didControl = true;                  // signal that we did a control command rather than preparing leg moves
}

void handle_fo_newHomeLCoords()
{  // the 18 numbers in the arguments are the new LOCAL coordinates of the home position
   // MQTT command processing put them into the flow arrays f_legX[f_active][L] ...

   for(L=1; L<=6; L++)           // for all the legs
   {
      f_dynLHomeX[L] = f_legX[f_active] [L];   // new dynamic home local coord is right out of flow command
      f_dynLHomeY[L] = f_legZ[f_active] [L];
      f_dynLHomeZ[L] = f_legX[f_active] [L];

      // we'll need to convert local coords to get equivalent global coords
      localCoordsToGlobal(L,f_dynLHomeX[L],f_dynLHomeY[L],f_dynLHomeZ[L]);
      // answers (global x,y,z) are returned in f_graphX, f_graphY, and f_graphZ
      f_dynGHomeX[L] = f_graphX;
      f_dynGHomeY[L] = f_graphY;
      f_dynGHomeZ[L] = f_graphZ;
   }
   f_active ++ ;                 // advance to flow row after the one with this control operation code
   didControl = true;                  // signal that we did a control command rather than preparing leg moves
}

void handle_fo_newHomeHere()        // new home position is now defined as current toe positions
{  // need to redefine both local and global home variables, f_dynLHomeX[l]... and f_dynGHomeX[L]...

   // the local part is easy - they're sitting in f_endLegX[L]... from last movement
   for (L=1; L<=6; L++)             // for all the legs...
   {
      f_dynLHomeX[L] = f_endLegX[L];   // new dynamic home local coord is end of line we just finished
      f_dynLHomeY[L] = f_endLegY[L]; 
      f_dynLHomeZ[L] = f_endLegZ[L]; 
      // we'll need to convert local coords to get equivalent global coords
      localCoordsToGlobal(L,f_dynLHomeX[L],f_dynLHomeY[L],f_dynLHomeZ[L]);
      // answers (global x,y,z) are returned in f_graphX, f_graphY, and f_graphZ
      f_dynGHomeX[L] = f_graphX;
      f_dynGHomeY[L] = f_graphY;
      f_dynGHomeZ[L] = f_graphZ;
   }
   f_active ++ ;                 // advance to flow row after the one with this control operation code
   didControl = true;                  // signal that we did a control command rather than preparing leg moves
}

void handle_fo_newHomeLReset()
{
// GLOBAL coords for each leg's home position
// these are now dynamic, due to the fo_newHomexxx flow operations
// these 6 lines are re-executed in the fo_newHomeReset operation
   f_dynGHomeX[1] =  18.62 ; f_dynGHomeY[1] = -14.79 ; f_dynGHomeZ[1] = -10.60 ; 
   f_dynGHomeX[2] =   0    ; f_dynGHomeY[2] = -20.71 ; f_dynGHomeZ[2] = -10.60 ;
   f_dynGHomeX[3] = -18.62 ; f_dynGHomeY[3] = -14.79 ; f_dynGHomeZ[3] = -10.60 ;
   f_dynGHomeX[4] =  18.62 ; f_dynGHomeY[4] =  14.79 ; f_dynGHomeZ[4] = -10.60 ;
   f_dynGHomeX[5] =   0    ; f_dynGHomeY[5] =  20.71 ; f_dynGHomeZ[5] = -10.60 ;
   f_dynGHomeX[6] = -18.62 ; f_dynGHomeY[6] =  14.79 ; f_dynGHomeZ[6] = -10.60 ;

// LOCAL coords for each leg's home position
// these are now dynamic, due to the fo_newHomexxx flow operations
// this is re-executed in the fo_newHomeReset operation
   for(int legnum=1; legnum<=6; legnum++) 
   {  f_dynLHomeX[legnum] = f_staticHomeX;   // initially, dynamic home is same as original home
      f_dynLHomeY[legnum] = f_staticHomeY;
      f_dynLHomeZ[legnum] = f_staticHomeZ;
   }
   f_active ++ ;                 // advance to flow row after the one with this control operation code
   didControl = true;              // signal that we did a control command rather than preparing leg moves
   return;
}

void handle_fo_toeSafetyX()
{}

void handle_fo_toeSafetyY()
{}

void handle_fo_toeSafetyZ()
{}

void handle_fo_toeSafetyReset()
{}

