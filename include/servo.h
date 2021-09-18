#ifndef servo_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define servo_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io
#include <Wire.h> // I2C communication.
#include <Adafruit_PWMServoDriver.h> // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library.
#include <main.h> // Header file for all libraries needed by this program.

#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates.
#define servoMiddlePWM 300 // 90 degree or center position of servo motor.
#define servoUpDownSwing 100 // Up and down PWM range for leg. 
#define servoFrontBackSwing 100 // Up and down PWM range for leg. 
#define numLegs 6 // Number of legs robot has.
#define numDrivers 2 // Number of servo motor drivers robot has.
Adafruit_PWMServoDriver pwmDriver[numDrivers]; // Servo driver object.
uint16_t pwmClkStart = 0; // Start value of count-up PWM high signal.
uint32_t oscFreq = 27000000; // Frequency of oscilator on motor driver. 
typedef struct
{
     String description; 
     int8_t driverAdd;
     int8_t hipPinNum;
     int8_t kneePinNum;
     int8_t toePinNum;
     int16_t maxUp;
     int16_t maxDown;
     int16_t maxFront;
     int16_t maxBack;
}legStruct;
legStruct leg[numDrivers][numLegs];
int8_t legDirIndex = 0; // What the legs are currently doing.
int8_t const legDirCnt = 10; // Number of things legs know how to do.
String legDirExpl[legDirCnt]; // Explanation of what each directive means. 

/**
 * @brief Put leg in neutral position.
 * 
 * @details Each leg is connected to a PWM pin on a servo motor driver. There 
 * are 2 motor drivers on hexbot. One driver handles all the motors used for 
 * the legs on the left side. Another motor driver handles all of the motors 
 * used for the right side. Each leg is made up of three joints. 
 * 
 * @param driver One of the 16 channel motor drivers (0-1).
 * @param leg One of the three legs on one side of the robot (0-2).
 * ==========================================================================*/
void startPositionLegs(int8_t driverNum, int8_t legNum) 
{
   Serial.print("<startPositionLeftLegs> Put ");
   Serial.print(leg[driverNum][legNum].description);
   Serial.println(" leg into neutral position.");
   Serial.println("...Move knee.");
   pwmDriver[driverNum].setPWM(leg[driverNum][legNum].kneePinNum, pwmClkStart, leg[driverNum][legNum].maxUp);
   delay(100);
   Serial.println("...Move hip.");
   pwmDriver[driverNum].setPWM(leg[driverNum][legNum].hipPinNum, pwmClkStart, servoMiddlePWM);
   delay(100);
   Serial.println("...Move toe.");
   pwmDriver[driverNum].setPWM(leg[driverNum][legNum].toePinNum, pwmClkStart, servoMiddlePWM);
   delay(100);
   legDirIndex = 0; // Indicate that legs are currently in home position.
} // startRightLeg()

/**
 * @brief Initialize serv motor control.
 * ==========================================================================*/
void initServo() 
{
   int8_t driver; // Left or right driver number
   int8_t legNum; // Front, middle or back leg on specific side

   Serial.println("<initServo> Set up Explanation for each motor directive.");
   legDirExpl[0] = "home position";
   legDirExpl[1] = "stand position";
   legDirExpl[3] = "crouch position";
   legDirExpl[4] = "lean left";
   legDirExpl[5] = "lean right";
   legDirExpl[6] = "lean forward";
   legDirExpl[7] = "lean backward";
   Serial.println("<initServo> Set up motor definitions for each leg on right driver.");
   driver = 0; // Right servo motor driver
   legNum = 0; // First leg on right side
   leg[driver][legNum].description = "right front";
   leg[driver][legNum].driverAdd = PCA9685ServoDriver1;
   leg[driver][legNum].hipPinNum = 0;
   leg[driver][legNum].kneePinNum = 1;
   leg[driver][legNum].toePinNum = 2;
   leg[driver][legNum].maxUp = servoMiddlePWM - servoUpDownSwing;
   leg[driver][legNum].maxDown = servoMiddlePWM + servoUpDownSwing;
   leg[driver][legNum].maxFront = servoMiddlePWM + servoFrontBackSwing;
   leg[driver][legNum].maxBack = servoMiddlePWM - servoFrontBackSwing;
   legNum ++; // Middle leg on right side
   leg[driver][legNum].description = "right middle";
   leg[driver][legNum].driverAdd = PCA9685ServoDriver1;
   leg[driver][legNum].hipPinNum = 3;
   leg[driver][legNum].kneePinNum = 4;
   leg[driver][legNum].toePinNum = 5;
   leg[driver][legNum].maxUp = servoMiddlePWM - servoUpDownSwing;
   leg[driver][legNum].maxDown = servoMiddlePWM + servoUpDownSwing;
   leg[driver][legNum].maxFront = servoMiddlePWM + servoFrontBackSwing;
   leg[driver][legNum].maxBack = servoMiddlePWM - servoFrontBackSwing;
   legNum ++; // Back leg on right side
   leg[driver][legNum].description = "right back";
   leg[driver][legNum].driverAdd = PCA9685ServoDriver1;
   leg[driver][legNum].hipPinNum = 6;
   leg[driver][legNum].kneePinNum = 7;
   leg[driver][legNum].toePinNum = 8;
   leg[driver][legNum].maxUp = servoMiddlePWM - servoUpDownSwing;
   leg[driver][legNum].maxDown = servoMiddlePWM + servoUpDownSwing;
   leg[driver][legNum].maxFront = servoMiddlePWM + servoFrontBackSwing;
   leg[driver][legNum].maxBack = servoMiddlePWM - servoFrontBackSwing;
   Serial.println("<initServo> Set up motor definitions for each leg on left driver.");
   driver = 1; // Left servo motor driver
   legNum = 0; // First leg on left side
   leg[driver][legNum].description = "left front";
   leg[driver][legNum].driverAdd = PCA9685ServoDriver2;
   leg[driver][legNum].hipPinNum = 0;
   leg[driver][legNum].kneePinNum = 1;
   leg[driver][legNum].toePinNum = 2;
   leg[driver][legNum].maxUp = servoMiddlePWM + servoUpDownSwing;
   leg[driver][legNum].maxDown = servoMiddlePWM - servoUpDownSwing;
   leg[driver][legNum].maxFront = servoMiddlePWM + servoFrontBackSwing;
   leg[driver][legNum].maxBack = servoMiddlePWM - servoFrontBackSwing;
   legNum ++; // Middle leg on left side
   leg[driver][legNum].description = "left middle";
   leg[driver][legNum].driverAdd = PCA9685ServoDriver2;
   leg[driver][legNum].hipPinNum = 3;
   leg[driver][legNum].kneePinNum = 4;
   leg[driver][legNum].toePinNum = 5;
   leg[driver][legNum].maxUp = servoMiddlePWM + servoUpDownSwing;
   leg[driver][legNum].maxDown = servoMiddlePWM - servoUpDownSwing;
   leg[driver][legNum].maxFront = servoMiddlePWM + servoFrontBackSwing;
   leg[driver][legNum].maxBack = servoMiddlePWM - servoFrontBackSwing;
   legNum ++; // Back leg on left side
   leg[driver][legNum].description = "left back";
   leg[driver][legNum].driverAdd = PCA9685ServoDriver2;
   leg[driver][legNum].hipPinNum = 6;
   leg[driver][legNum].kneePinNum = 7;
   leg[driver][legNum].toePinNum = 8;
   leg[driver][legNum].maxUp = servoMiddlePWM + servoUpDownSwing;
   leg[driver][legNum].maxDown = servoMiddlePWM - servoUpDownSwing;
   leg[driver][legNum].maxFront = servoMiddlePWM + servoFrontBackSwing;
   leg[driver][legNum].maxBack = servoMiddlePWM - servoFrontBackSwing;
   Serial.println("<initServo> Initialize I2C bus0.");
   Wire.begin(I2C_BUS0_SDA, I2C_BUS0_SCL, I2C_bus0_speed);
   Serial.println("<initServo> Initialize servo driver 0 - right.");
   pwmDriver[0] =  Adafruit_PWMServoDriver(PCA9685ServoDriver1); 
   pwmDriver[0].begin();
   pwmDriver[0].setOscillatorFrequency(oscFreq);
   pwmDriver[0].setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
   delay(10);
   Serial.println("<initServo> Initialize servo driver 1 - left.");
   pwmDriver[1] =  Adafruit_PWMServoDriver(PCA9685ServoDriver2); 
   pwmDriver[1].begin();
   pwmDriver[1].setOscillatorFrequency(oscFreq);
   pwmDriver[1].setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
   delay(10);
   for(int8_t driverNum = 0; driverNum < 2; driverNum++) // Loop through drivers
   {
      for(int8_t legNum = 0; legNum < 3; legNum++) // Loop through motors
      {
         startPositionLegs(driverNum, legNum); // Put leg into starting position 
      } // for
   } // for
} // initServo()

#endif // End of precompiler protected code block