/*******************************************************************************
 * @file daeIK.cpp  
 * @brief File containing all of Doug's inverse kinematic functions.
 *******************************************************************************/
#ifndef daeIK_cpp // Start of precompiler check to avoid dupicate inclusion of 
                  // this code block.

#define daeIK_cpp // Precompiler macro used for precompiler check.

#include <main.h> // Includes used by  this project.

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

/**
 * @brief Show how to call each daeIK function.
 * @details In  order to "return" multile values from a function we can pass
 * the address of local variables to the function and that function will 
 * populate those variables by using pointers to them. 
 * ==========================================================================*/
void testDaeIKFunctions()
{
/* think this code has served it's purpose,  & doesn't need to be updated as changes are made   
   Log.noticeln("<testDaeIKFunctions> Testing Doug's IK functions.");
   
   float degrees = 90;
   float centerDeg = 90;
   Log.noticeln("<testDaeIKFunctions> ... Example call to mapDegToPWM(%F, %F).", degrees, centerDeg);
   int32_t pwm = mapDegToPWM(degrees, centerDeg);
   Log.noticeln("<testDaeIKFunctions> ...... PWM for %F degrees with a center of %F = %D", degrees, centerDeg, pwm);
  
   float x = 7; // Toe target x position.
   float y = -2.63; // Toe target y position.
   float z = 0; // Toe target z position.
   float f_angH;
   float f_angK;
   float f_angA;
   Log.noticeln("<testDaeIKFunctions> ... Example call to coordsToAngles(%F, %F, %F).", x, y, z);
   coordsToAngles(x, y, z); // Maybe return True/false for valid solution?
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
*/
} // testFunctions()

#endif // End of precompiler protected code block