/*******************************************************************************
 * @file daeIK.h  
 *******************************************************************************/
#ifndef daeIK_h // Start of precompiler check to avoid dupicate inclusion of 
                // this code block.

#define daeIK_h // Precompiler macro used for precompiler check.

/*******************************************************************************
 * @section daeIKIncludes Included libraries.
 *******************************************************************************/
#include <main.h> // Includes used by  this project.

/*******************************************************************************
 * @section daeGlobalVars Global variables.
 *******************************************************************************/
const uint8_t footLen = 11; // Distance from ankle to toe (foot) is 11cm. 
const uint8_t shinLen = 7.5; // Distance from knee to ankle (shin) is 7.5cm.
const uint8_t toeOffset = 17; // Angle that toe is offset from 90deg of ankle joint is 17 degrees.
const uint8_t origXOffset = 2.92; // Distance the knee is offset from the origin along the x axis.
   
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
int32_t mapDegToPWM(float *degrees, float *centerDeg)
{
   const int8_t offset = 90; // Angle offset of motor in neutral position?
   // TODO #26 create constants for all magic numbers in this function. 
   if(*degrees < *centerDeg - offset) // range check the desired degrees value
   {
      *degrees = *centerDeg - offset;
   } // if
   if(*degrees > *centerDeg + offset) // range check the desired degrees value
   {
      *degrees = *centerDeg + offset;
   } // if
   // formula fits a line to two measured data points (x=degrees, y=PWM) with 
   // the points selected to minimize overall errors: (24,160) (166,460)
   // formula is based on y = M * x + b where M is the slope, 
   // (delta Y)/(delta X) for 2 selected points b is the y intercept, derived 
   // by substituting a selected point into above formula after slope is known.
   return (*degrees - (*centerDeg - offset)) * 300 / 142 + 109.3;
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
 * @param *f_angH address where hip angle (in degrees) is stored.
 * @param *f_angK address where knee angle (in degrees) is stored.
 * @param *f_angA address where ankle angle (in degrees) is stored.
 * @return converted angles for the hip, knee and ankle are written to the 
 * memory locations passed as arguments to this function and can therefore be 
 * accessed directly by the calling function.
 * ==========================================================================*/
void coordsToAngles(float x, float y, float z, float *f_angH, float *f_angK, float *f_angA)    
{
   // TODO #27 create constants for all magic numbers in this function.
   float f_Ux, f_Uy; // toe position when rotated into xy plane.
   *f_angH = atan(radians(z / x)); // the hip angle is the easy one.

   // now reduce to a 2D problem by rotating leg into xy plane (around y axis)
   // resulting in new x coordinate: Ux. ( Uy stays same as original y, and new Uz = 0)
   // using standard formula for rotating a 2D vector with angle opposite to hip angle...
   f_Ux = x * cos(radians(- *f_angH)) - z * sin(radians(- *f_angH));
   f_Uy = y; // the rotation doesn't change the y value
   // spreadsheet: =(E7*COS(-I7/180*PI()) - G7*SIN(-I7/180*PI()))

   // next we deduce where the ankle has rotated to in the xy plane
   // the scary math is explained in another document, but here's a summary:
   // -ankle lies on a circle with radius 7.5 centred on knee servo
   // -ankle also lies on a circle with radius 11, centred on the toe = (x,y,z)
   // this provides 2 equations in 2 unknowns (Ax, Ay), but they're quadratic and have
   // 2 solutions. (this makes sense, because those 2 circles intersect in 2 places)
   // reformulate the equations into a single quadratic equation in one variable,
   // apply the quadratic formula, and be clever in selecting the right solution.
   //
   // A quadratic equation has the form A*x^2 + B*x + C = 0
   // the quadratic formula is: x = ( -B +/- SQRT(B*B - 4*a)) / (2*A)
   //   (the +/- choice is what gives 2 solutions )
   // time to calculate the quadratic coefficients A, B, and C
   float f_QA = 1 + (25 - 20*f_Ux + 4 * f_Ux * f_Ux) / (4 * y * y);
   float f_QB = -5 + (10 * (-71 + f_Ux * f_Ux + y * y) -4 * ((-71 + f_Ux * f_Ux + y * y) * f_Ux)) / (4 * y * y);
   float f_QC = -50 + ((-71.0 + f_Ux * f_Ux + y * y) * (-71.0 + f_Ux * f_Ux + y * y)) / (4 * y * y);

   // here comes the quadratic formula, which produces two possible solutions due to the +/-
   //  we'll comput them both, then make a choice based on robot limitations
   //  generally, we want the one where the ankle is the highest, maximizing Ay
   float f_Ax, f_Ay, f_AxPlus, f_AxMinus, f_AyPlus, f_AyMinus; // coordinates of ankle, rotated into xy plane
   float f_determinant; // detrminant in quadratic solution - must be >= 0
   f_determinant = round((f_QB * f_QB - 4 * f_QA * f_QC) * 10000) / 10000;
   if(f_determinant < 0) 
   { 
      Log.noticeln("========= negative determinant =======");
   } // if
   f_AxPlus  = (-1 * f_QB + sqrt(f_determinant)) / (2 * f_QA);
   f_AxMinus = (-1 * f_QB - sqrt(f_determinant)) / (2 * f_QA);
   // substituting back in previous equation to get correcponding Ay valus
   f_AyPlus  = ((-71 + f_Ux * f_Ux + f_Uy * f_Uy) -f_AxPlus *(-5 + 2 * f_Ux)) / (2 * y);
   f_AyMinus = ((-71 + f_Ux * f_Ux + f_Uy * f_Uy) -f_AxMinus *(-5 +2 * f_Ux)) / (2 * y);
   // initially, guess that we're using the (Ax,Ay) pair with the "+" in quadratic solution
   f_Ax = f_AxPlus;
   f_Ay = f_AyPlus;
   // but swap if the other coordinates have a higher Y value, and the X value is on positive side of knee,
   // .. which means knee can reach it without exceeding 90 degrees  
   if(f_AyMinus > f_AyPlus && f_AxMinus >= origXOffset)
   {  
      f_Ax = f_AxMinus;
      f_Ay = f_AyMinus;
   } // if
   // however, if that puts x to the -ve side of knee, where ankle can't go, pick the other case
//   if(f_Ax < origXOffset)
//   {  f_Ax = f_AxPlus;
//      f_Ay = f_AyPlus;
//   }
   // there are still some unlikely edge cases needing attention, such as h=0, k=-44, a=75

//spr("`AxPlus,AyPlus= "); spr(f_AxPlus); sp; spl(f_AyPlus);
//spr("`AxMinus,AyMinus= "); spr(f_AxMinus); sp; spl(f_AyMinus);
//spr("`Ax,Ay= "); spr(f_Ax); sp; spl(f_Ay);

// think following stuff is obsolete, but keeping the formulas
   // get y by substituting x into a previous equation, again dependent on sign of y
//    if(y>0)   {f_Ay = -1*((-71+f_Ux*f_Ux+y*y) - f_Ax*(-5+2*f_Ux))/(2*y);}
//    if(y<=0)  {f_Ay =    ((-71+f_Ux*f_Ux+y*y) - f_Ax*(-5+2*f_Ux))/(2*y);}

    // now that we know where the ankle is, we can finally work on the angles
    // the knee is easy since we defind the ankle position above
    *f_angK = -1 * asin(radians(f_Ay / shinLen));    

// there are 4 possible cases for ankle position, with different calculations for A angle
// 1) Ux>origXOffset, Uy<0  // the normal case, toe below knee
// 2) Ux>origXOffset, Uy>=0  // still normal, toe above knee
// 3) Ux<origXOffset, Uy>0  // unreachable if servo angle limited to 90 degrees
// 4) Ux<origXOffset, Uy=<0  // toe is underneath robot

// should put in defenses for unreasonable angles being returned

// for cases 1 and 4
   if(f_Uy < 0)
   {
      float f_P = asin(radians(f_Ux - f_Ax) / footLen);      // can only explain this with a diagram
      *f_angA = f_P + *f_angK - toeOffset;
   }  // Uy <0

// for cases 2, and impossible 3
   if(f_Uy >= 0)
   {
      float f_R = asin(radians(f_Uy - f_Ay) / footLen);      // can only explain this with a diagram
      *f_angA = f_R + 90 + *f_angK - toeOffset;
   }  // Uy <0   
} // coordsToAngles()

/**
 * @brief Show how to call each daeIK function.
 * @details In  order to "return" multile values from a function we can pass
 * the address of local variables to the function and that function will 
 * populate those variables by using pointers to them. 
 * ==========================================================================*/
void testDaeIKFunctions()
{
   Log.noticeln("<testDaeIKFunctions> Testing Doug's IK functions.");
   
   float degrees = 90;
   float centerDeg = 90;
   Log.noticeln("<testDaeIKFunctions> ... Example call to mapDegToPWM(%F, %F).", degrees, centerDeg);
   int32_t pwm = mapDegToPWM(&degrees, &centerDeg);
   Log.noticeln("<testDaeIKFunctions> ...... PWM for %F degrees with a center of %F = %D", degrees, centerDeg, pwm);
  
   float x = 7; // Toe target x position.
   float y = -2.63; // Toe target y position.
   float z = 0; // Toe target z position.
   float f_angH;
   float f_angK;
   float f_angA;
   Log.noticeln("<testDaeIKFunctions> ... Example call to coordsToAngles(%F, %F, %F).", x, y, z);
   coordsToAngles(x, y, z, &f_angH, &f_angK, &f_angA); // Maybe return True/false for valid solution?
   Log.noticeln("<testDaeIKFunctions> ...... Set hip joint to %F degrees, knee joint to %F degrees and ankle joint to %F", f_angH, f_angK, f_angA);

   float hip = 45.0;
   float knee = 45.0;
   float ankle = 45.0;
   float toeX;
   float toeY;
   float toeZ;
   Log.noticeln("<testDaeIKFunctions> ... Example call to anglesToCoords(%F, %F, %F).", hip, knee, ankle);
   anglesToCoords(hip, knee, ankle, &toeX, &toeY, &toeZ);
   Log.noticeln("<testDaeIKFunctions> ...... Set toeX to %F, toeY to %F and toeZ to %F", toeX, toeY, toeZ);
} // testFunctions()

#endif // End of precompiler protected code block