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
#define PCA9685 0x40 // Servo controller I2C address.
#define LCD16x2 0x3F // Liquid Crystal Display.
#define PCA9685ServoDriverAllCall 0x70 // Global I2C address for all servo drivers.
#define PCA9685ServoDriver1 0x40 // First servo driver.
#define PCA9685ServoDriver2 0x41 // Second servo driver.
#define PCA9685ServoDriver3 0x42 // Third servo driver.
#define PCA9685ServoDriver4 0x43 // Fourth servo driver.
#define PCA9685ServoDriver5 0x44 // Fifth servo driver.
#define PCA9685ServoDriver6 0x45 // Sixth servo driver.
#define PCA9685ServoDriver7 0x46 // Seventh servo driver.

/*************************************************************************************************************************************
 * @brief Identify a device based on its I2C address
 * @param deviceAddress I2C address of the device to be identified
 *************************************************************************************************************************************/
void identifyDevice(int deviceAddress)
{
  Serial.print ("<identifyDevice> Device with I2C address ");
  Serial.print (deviceAddress, DEC);
  Serial.print (" (0x");
  Serial.print (deviceAddress, HEX);
  Serial.print (") ");
  switch (deviceAddress) 
  {
    case rightOLED_I2C_ADD:    
      Serial.println(" identified as Right OLED");
      break;
    case leftOLED_I2C_ADD:    
      Serial.println(" identified as Left OLED");
      break;
    case dcMotorController:    
      Serial.println(" identified as MD25 motor controller");
      break;
    case MPU6050_I2C_ADD:
      Serial.println(" identified as MPU6050");
      break;
    case LCD16x2:
      Serial.println(" identified as 16x2 LCD screen");
      break;
    case PCA9685ServoDriverAllCall:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver ALL CALL");
      break;
    case PCA9685ServoDriver1:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver 1");
      break;
    case PCA9685ServoDriver2:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver 2");
      break;
    case PCA9685ServoDriver3:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver 3");
      break;
    case PCA9685ServoDriver4:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver 4");
      break;
    case PCA9685ServoDriver5:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver 5");
      break;
    case PCA9685ServoDriver6:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver 6");
      break;
    case PCA9685ServoDriver7:
      Serial.println(" identified as PCA9685 16-channel 12-bit servo motor driver 7");
      break;
    default: 
      Serial.println("Identified as UKNOWN");
      break;
  } //switch
} //identifyDevice()

/*************************************************************************************************************************************
 * @brief Scan I2C bus0 aka wire()
 * 
 * @param deviceAddress 
 *************************************************************************************************************************************/
void scanBus0()
{
  Serial.println ("<scanBus0> Scan I2C bus 0 looking for devices...");
  byte count = 0;
  for (byte i = 8; i < 120; i++)
  { 
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
    {
      Serial.print ("<scanBus0> Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      identifyDevice(i); // Identify what device has been found 
      delay (1);
    } // end of good response
  } // end of for loop
  Serial.println ("<scanBus0> Done.");
  Serial.print ("<scanBus0> Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
} //scanBus0()

/*************************************************************************************************************************************
 * @brief Scan I2C bus1 aka wire1()
 * 
 * @param deviceAddress 
 *************************************************************************************************************************************/
void scanBus1()
{
  Serial.println ("<scanBus1> Scan I2C bus 1 looking for devices...");
  byte count = 0;
  for (byte i = 8; i < 120; i++)
  { 
    Wire1.beginTransmission (i);
    if (Wire1.endTransmission () == 0)
    {
      Serial.print ("<scanBus1> Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      identifyDevice(i); // Identify what device has been found 
      delay(1);
    } // end of good response
  } // end of for loop
  Serial.println ("<scanBus1> Done.");
  Serial.print ("<scanBus1> Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
} //scanBus1()
#endif // End of precompiler protected code block