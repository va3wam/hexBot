#ifndef ikLibrary_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define ikLibrary_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.
#include <InverseK.h> // Inverse kinematic library for leg movement algorithms.

/**
 * @brief Calculate angles for the leg joint in order to move toe to target 
 *        coordinates in a 3 axis cartesian grid.
 * @param driverNum is the number referring to which servo motor driver 
 *                  controls the current leg. Valid values are 0 or 1.
 * @param legNum is the number referring to which leg we are currently working 
 *               on. Valid leg numbers are 0-2.
 * @param _x_ is the target x coordinate we want to move to.
 * @param _y_ is the target y coordinate we want to move to.
 * @param _z_ is the target z coordinate we want to move to.
 * @return TRUE if there is a valid solution or FALSE if there is not.
 * ==========================================================================*/
bool calcAngles(int8_t driverNum, int8_t legNum, float _x_, float _y_, float _z_)
{
//   InverseK.attach(leg[driverNum][legNum].hip, 
//                     leg[driverNum][legNum].knee, 
//                     leg[driverNum][legNum].ankle, 
//                     leg[driverNum][legNum].toe); // Attach links to kinematic model.
//   return InverseK.solve(_x_, 
//                  _y_, 
//                  _z_, 
//                  hipAngle, 
//                  kneeAngle, 
//                  ankleAngle, 
//                  toeAngle); // this returns TRUE or FALSE
   return false;
} // calcAngles()

#endif // End of precompiler protected code block