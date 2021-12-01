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

   
}
// standard doxygen docs here
float lx, ly, lz;
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
        *lz = Xrt;        
          
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
        *lx = Yrt;
        *lz = Xrt;        
        break;
      default:
        return false;
   }
   return true;
}
/*
float fp_frontToeHomeX = 3.82739 + 20.91875 * .707107;   // 707107 is sin of 45 degrees
float fp_frontToeHomeY = 20.91875 * .707107;
float fp_sideToeHomeX = 0;
float fp_sideToeHomeY = 6.9423 + 2.9165 + 7.61998 + 3.23019;

float fp_frontHipX = 3.82739 + 7.13528 * .707107;
float fp_frontHipY = 5.04750;
float fp_sideHipX = 0;
float fp_sideHipY = 6.9423;
*/

// do_flow is triggered by the MQTT flow_go command, which sets f_flowing to true
// f_active is initially zero, which initiates various setup activities on first do_flow entry
// in general case, do_flow executes a small servo movement on all 3 servos, at a calculated time interval

void do_flow()          // called from loop if there's a flow executing that needs attention
{
   
//   float f_frameHip, f_frameKnee, f_frameAnkle;

// recode from scratch
   if(f_active == 0)                // starting a new flow, so need to do some setup
   {  sp1l("--initial toe offsets--");
      for(int l=1; l<=6; l++)     // copy flow coords into  working vectors
      {  f_lastLegX[l] = f_legX[f_active][l];  
         f_lastLegY[l] = f_legY[f_active][l]; 
         f_lastLegZ[l] = f_legZ[f_active][l]; 
         sp2s(f_lastLegX[l],f_lastLegY[l]); sp2l(" ",f_lastLegZ[l]);
      }
      // we need local coords to be able to give commands to servos
      // the operation code in f_operation[f_active] tells us what king of coords we were given
      f_goodData = true;               // assume thing will go well, & f_operation is valid
      if(f_operation[f_active] == fo_moveRelHome || f_operation[f_active] == fo_startRelHome)
      {  // we were given offsets relative to home position, so add in home coords
         sp1l("--global toe coords including offsets--");
         int l;
         for(l=1; l<=6; l++)  // add offset to home's global coord, to get final global coord
         {  f_tmpX[l] = f_lastLegX[l] + f_homeX[l];   
            f_tmpY[l] = f_lastLegY[l] + f_homeY[l];
            f_tmpZ[l] = f_lastLegZ[l] + f_homeZ[l];
            sp2s(f_tmpX[l],f_tmpY[l]); sp2l(" ",f_tmpZ[l]);
         }
         // now convert final global coords to local coords we can feed to servos
         sp1l("--final local coords including offsets--");
         for(int l=1; l<=6; l++)  // add offset to home's global coord, to get final global coord
         {  globCoordsToLocal(l,f_tmpX[l],f_tmpY[l],f_tmpZ[l],&f_lastLegX[l],&f_lastLegY[l],&f_lastLegZ[l]);
            sp2s(f_lastLegX[l],f_lastLegY[l]); sp2l(" ",f_lastLegZ[l]);
         }
         

      }
      else if (f_operation[f_active] == fo_moveAbs || f_operation[f_active] == fo_startAbs)
      {  // we were given absolute coords, and need to convert to local coords
         // if we're in flow start up, we're looking at flow row 0, thus [0] below
         for(int l=1; l<=6; l++)   // l stands for leg. short to avoid cobol expression syndrome
         {  globCoordsToLocal(l,f_legX[0][l],f_legY[0][l],f_legZ[0][l],&f_lastLegX[l],&f_lastLegY[l],&f_lastLegZ[l]);
         }
      }
      else
      {  // unsupported op code in first row - abort
         f_flowing = false;         // stop executing the flow
         f_goodData = false;        // bypass rest of do_flow processing
         // need to avoid falling into following code. use a flag for "good data seen" ?
      }
      // this would be a good time to do a validity check on the local coords for the requested toe position
      //
      // -one approach is to allow positions within a certain radius of the home position, i.e. a safe sphere
      //  radius is SQRT( (local X)^2 + (local Y)^2 + (local Z)^2 )
      //  if radius > max-radius-parameter, abort and set f_goodData = false
      //
      // -second approach is to allow positions within a box centered at home position
      //  define maximum deviations from home: maxX, maxY and maxZ 
      //  you're safe if abs(x) <= maxX && abs(y) <= maxY && abs(z) <= maxZ
      //  but I digress...

      if(f_goodData)
      {  // lastLeg?[leg] contains the local coords of the position we need to jump to
         for(int l=1; l<=6; l++)
         {  // move each leg to the position in local coords in f_lastLegX[l], f_lastLegY[l], f_lastLegZ[l]
            // the call that actually moves servo is pwmDriver[driver].setPWM[pin, pwmClkStart, pwm-value]
            //   the driver we can lookup in legIndexDriver[leg]
            //   the pin can be derived from legIndexHipPin[leg]
            //   to get pwm value, we convert local coords to angles, then from angles to pwm values
            float f_angH, f_angK, f_angA ;      // temp variables to hold servo angles
            Log.noticeln(" X: %5.2f, Y: %5.2f, Z: %5.2f",f_lastLegX[l], f_lastLegY[l], f_lastLegZ[l]);
            coordsToAngles(f_lastLegX[l], f_lastLegY[l], f_lastLegZ[l], &f_angH, &f_angK, &f_angA); 
            Log.noticeln("<do_flow> Leg %u, angH = %.2f, angK = %.2f, angA = %.2f",l,f_angH,f_angK,f_angA);

            // now, one servo wihin the leg at a time, figure the pwm value, and move the servo
            // starting with the hip...
//pwmDriver[driverNum].setPWM(leg[driverNum][legNum].hipPinNum, pwmClkStart, servoMiddlePWM);
            pwmDriver[legIndexDriver[l]].setPWM(legIndexHipPin[l],  pwmClkStart, mapDegToPWM(f_angH,0));
            Log.noticeln("H: Driver=%d,  Pin=%d, angH=%.2f,  pwm=%.2fd",legIndexDriver[l],legIndexHipPin[l],f_angH, mapDegToPWM(f_angH,0));
            pwmDriver[legIndexDriver[l]].setPWM(legIndexHipPin[l]+1,pwmClkStart, mapDegToPWM(f_angK,0));
            Log.noticeln("H: Driver=%d,  Pin=%d, angH=%.2f,  pwm=%.2f",legIndexDriver[l],legIndexHipPin[l]+1,f_angK, mapDegToPWM(f_angK,0));
            pwmDriver[legIndexDriver[l]].setPWM(legIndexHipPin[l]+2,pwmClkStart, mapDegToPWM(f_angA,0));
            Log.noticeln("H: Driver=%d,  Pin=%d, angH=%.2f,  pwm=%.2f",legIndexDriver[l],legIndexHipPin[l]+2,f_angA, mapDegToPWM(f_angA,0));
            // ok, the 3 servos in that leg have been moved - on to the next leg
         }  // for l = 1 to 6
         f_flowing = false;            // that's all I've coded so far   
        
      }
      // if (f_goodData) {} else
      // good do a safety check on data:
      //    - toe within a certain radius of home position
      //    - toe within a safe zone on each local axis
      
   }
   else if( f_active > 0)
   {

   }
   else
   {
     // f_active went negative - abort
     f_flowing = 0;
   }

// ================================================================================

   if(f_active > 0)     // we're past initialization, and working thru angle changes, a frame at a time
   /*  Need a diagram to visualize frames between positions

                    f_active  f_frame  flow arrays
   1st position         1        1      [0] +
      (50 ms)           1        1
      frame 1           1       1>2
      (50 ms)           1        2
      frame 2           1       2>3
    ...
      frame 19          1       19>20
      (50 ms)           1        20
    frame 20 = 2nd pos  2       20>1     [1] +

   */
   {
  /*  needs a lot of work, and generates a lot of errors

      if(millis() >= f_nextTime )       // if we've waited until next frame time
      {  
         f_frameHip = f_hip[f_active-1] + (f_frame/f_framesPerPosn) * f_deltaHip;   // figure servo positions
         f_frameKnee = f_knee[f_active-1] + (f_frame/f_framesPerPosn) * f_deltaKnee;
         f_frameAnkle = f_ankle[f_active-1] + (f_frame/f_framesPerPosn) * f_deltaAnkle;

         // move servo's a fraction of the way to next position
         pwm.setPWM(servoMotor[1].driverPort, SERVO_START_TICK, mapDegToPWM(f_frameHip, 0)); // Hip
         pwm.setPWM(servoMotor[2].driverPort, SERVO_START_TICK, mapDegToPWM(f_frameKnee, 0)); // Knee
         pwm.setPWM(servoMotor[3].driverPort, SERVO_START_TICK, mapDegToPWM(f_frameAnkle, 0)); // Ankle 
 
//////////// sprs(f_active);sprs(f_frame);  sprs(f_frameHip); sprs(f_frameKnee); spl(f_frameAnkle);

         f_frame = f_frame + 1 ;           // on to next frame within this position
//////////// spr2("f_frame=",f_frame); spr2(",  f_active=",f_active); nl;

         f_nextTime = millis() + int(f_msecs[1] / f_framesPerPosn +.5);
///////////// sprs("times/ac>0: "); sprs(millis()); spl(f_nextTime);
         if(f_frame > f_framesPerPosn)       // did we finish all frame for this position?
         {
            // yup, so we must be sitting at the next position. reorganize for next set of frames
            f_active ++ ;
            if(f_active < f_count )
            {                          // haven't run out of positions yet, so do frames out to the next one
               f_deltaHip = f_hip[f_active] - f_hip[f_active-1];   // figure the angle to be travelled for hip to next position
               f_deltaKnee = f_knee[f_active] - f_knee[f_active-1];
               f_deltaAnkle = f_ankle[f_active] - f_ankle[f_active-1];
////////////////sprs("deltas-2: "); sprs(f_deltaHip); sprs(f_deltaKnee); spl(f_deltaAnkle);               

               f_frame = 1;     // starting a new set of frames
//////////////// spl("just reset f_frame");
               f_nextTime = millis() + int(f_msecs[f_active] / f_framesPerPosn +.5);   //get speed info from next position

            }
            else    // ran out of positions. do we need to do more cycles?
            {
                  // cycles not implemented. stop after first
                  f_nextTime = 0;         // stop any further frame processing from moving servos
                  f_flowing = false;      // exit from flow processing
            }

         } // if f_frame > f_framesPerPosn
      } //if millis > f_nextTime
   } // if f_active > 0

   if(f_active == 0 )         // if this is first call to do_flow after MQTT flow_go command...
   {
      // move the servos in parallel at top speed to angles in first array entry
      pwm.setPWM(servoMotor[1].driverPort, SERVO_START_TICK, mapDegToPWM(f_hip[0], 0)); // Hip
      pwm.setPWM(servoMotor[2].driverPort, SERVO_START_TICK, mapDegToPWM(f_knee[0], 0)); // Knee
      pwm.setPWM(servoMotor[3].driverPort, SERVO_START_TICK, mapDegToPWM(f_ankle[0], 0)); // Ankle 
      delay(510);          // worst case delay to let servos move
///////////////// sptv("f_hip[0] ",f_hip[0]); sp; spr(f_knee[0]); sp; spl(f_ankle[0]);
///////////////// sptv("f_hip[1] ",f_hip[1]); sp; spr(f_knee[1]); sp; spl(f_ankle[1]);
      
      f_deltaHip = f_hip[1] - f_hip[0];   // figure the angle to be travelled for hip to next position
      f_deltaKnee = f_knee[1] - f_knee[0];
      f_deltaAnkle = f_ankle[1] - f_ankle[0];

///////////////// sprs("deltas: "); sprs(f_deltaHip); sprs(f_deltaKnee); spl(f_deltaAnkle);

      // we're setting servos at f_framesPerPosn frames between positions.
      // calculate initial time delay until 1st reposition, in rounded integer milliseconds
      // and schedule next flow processing
      f_nextTime = millis() + int(f_msecs[1] / f_framesPerPosn +.5);
      sprs("times: "); sprs(millis()); spl(f_nextTime);
      f_frame = 1;      // frame number we'll do next
      f_active = 1;     // we're now working towards the position in index 1 of the flow arrays
*/   //needs work
   } // if f_active = 0

}// void do_flow
