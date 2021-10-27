#ifndef i2c_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define i2c_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

/**
 * @brief Monitor local web service to see if there are any client requests.
 * @details Call to checkForClientRequest() does two things. First, it causes the 
 * localWebServer service to process any new binay downloads. Second, it returns a 
 * boolean, that when TRUE, indicates there is a new IP address for the MQTT broker 
 * that needs to be saved to NV RAM.
 * =================================================================================*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Define I2C bus0 - wire() - constants, classes and global variables 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define I2C_bus0_speed 400000 // Define speed of I2C bus 2. Note 400KHz is the upper speed limit for ESP32 I2C
#define I2C_bus0_SDA 23 // Define pin on the board used for Serial Data Line (SDA) for I2C bus 0
#define I2C_bus0_SCL 22 // Define pin on the board used for Serial Clock Line (SCL) for I2C bus 0

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Define I2C bus1 - wire1() - constants, classes and global variables 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define I2C_bus1_speed 100000 // Define speed of I2C bus 2. Note 100KHz is the upper speed limit for ESP32 I2C
#define I2C_bus1_SDA 17 // Define pin on the board used for Serial Data Line (SDA) for I2C bus 1
#define I2C_bus1_SCL 21 // Define pin on the board used for Serial Clock Line (SCL) for I2C bus 1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief Define I2C device addresses 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define MPU6050_I2C_ADD 0x68 // GY521 I2C address.
#define leftOLED_I2C_ADD 0x3D // OLED used for robot's left eye I2C adddress.
#define rightOLED_I2C_ADD 0x3C // OLED used for robot' right eye I2C address.
#define dcMotorController 0xB0 >> 1 // Wire Library only uses 7 bit addresses so you need to shift address one bit to the right.
#define LCD16x2 0x3F // Liquid Crystal Display.
#define PCA9685ServoDriverAllCall 0x70 // Global I2C address for all servo drivers.
#define PCA9685ServoDriver1 0x40 // I2C address for first servo driver.
#define PCA9685ServoDriver2 0x41 // I2C address for second servo driver.
#define PCA9685ServoDriver3 0x42 // I2C address for third servo driver.
#define PCA9685ServoDriver4 0x43 // I2C address for fourth servo driver.
#define PCA9685ServoDriver5 0x44 // I2C address for fifth servo driver.
#define PCA9685ServoDriver6 0x45 // I2C address for sixth servo driver.
#define PCA9685ServoDriver7 0x46 // I2C address for seventh servo driver.

/*************************************************************************************************************************************
 * @brief Identify a device based on its I2C address
 * @param deviceAddress I2C address of the device to be identified
 *************************************************************************************************************************************/
void identifyDevice(int deviceAddress)
{
  switch (deviceAddress) 
  {
    case rightOLED_I2C_ADD:    
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as Right OLED", deviceAddress, deviceAddress);
      oledConnected = true;
      break;
    case leftOLED_I2C_ADD:    
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as Left OLED", deviceAddress, deviceAddress);
      break;
    case dcMotorController:    
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as MD25 motor controller", deviceAddress, deviceAddress);
      break;
    case MPU6050_I2C_ADD:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as MPU6050", deviceAddress, deviceAddress);
      break;
    case LCD16x2:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as 16x2 LCD screen", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriverAllCall:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver ALL CALL", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriver1:
      motorController1Connected = true;
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver 1", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriver2:
      motorController2Connected = true;
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver 2", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriver3:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver 3", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriver4:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver 4", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriver5:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver 5", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriver6:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver 6", deviceAddress, deviceAddress);
      break;
    case PCA9685ServoDriver7:
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) identified as PCA9685 16-channel 12-bit servo motor driver 7", deviceAddress, deviceAddress);
      break;
    default: 
      Log.noticeln("<identifyDevice> Device with I2C address %d (%X) Identified as UKNOWN");
      break;
  } //switch
} //identifyDevice()

/*************************************************************************************************************************************
 * @brief Scan I2C bus0 aka wire()
 *************************************************************************************************************************************/
void scanBus0()
{
   Log.noticeln("<scanBus0> Scan I2C bus 0 looking for devices...");
   byte count = 0;
   for (byte i = 8; i < 120; i++)
   { 
      Wire.beginTransmission (i);
      if (Wire.endTransmission () == 0)
      {
         Log.noticeln("<scanBus0> Found address: %d (%X).", i, i);
         count++;
         identifyDevice(i); // Identify what device has been found 
         delay(1);
      } // if
   } // for
   Log.noticeln("<scanBus0> Done. Found %d device(s).", count);
} //scanBus0()

/*************************************************************************************************************************************
 * @brief Scan I2C bus1 aka wire1()
 *************************************************************************************************************************************/
void scanBus1()
{
   Log.noticeln("<scanBus1> Scan I2C bus 1 looking for devices...");
   byte count = 0;
   for (byte i = 8; i < 120; i++)
   { 
      Wire1.beginTransmission (i);
      if (Wire1.endTransmission () == 0)
      {
         Log.noticeln("<scanBus1> Found address: %d (%X).", i, i);
         count++;
         identifyDevice(i); // Identify what device has been found 
         delay(1);
      } // if
   } // for
   Log.noticeln("<scanBus0> Done. Found %d device(s).", count);
} //scanBus1()
#endif // End of precompiler protected code block