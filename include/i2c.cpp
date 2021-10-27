/*******************************************************************************
 * @file i2c.cpp  
 * @brief File containing all I2C functions.
 *******************************************************************************/
#ifndef i2c_cpp // Start of precompiler check to avoid dupicate inclusion of this code block.

#define i2c_cpp // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

/**
 * @brief Monitor local web service to see if there are any client requests.
 * @details Call to checkForClientRequest() does two things. First, it causes the 
 * localWebServer service to process any new binay downloads. Second, it returns a 
 * boolean, that when TRUE, indicates there is a new IP address for the MQTT broker 
 * that needs to be saved to NV RAM.
 * =================================================================================*/

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