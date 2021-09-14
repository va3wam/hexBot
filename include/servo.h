#ifndef servo_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define servo_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io
#include <Wire.h> // I2C communication.
#include <Adafruit_PWMServoDriver.h> // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library.
#include <main.h> // Header file for all libraries needed by this program.

#define SERVOMIN  100 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  400 // This is the 'maximum' pulse length count (out of 4096)
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates
#define north 300 // 90 degree or center position of servo motor
#define east 480 // 0 degree or east position of servo motor
#define west 115 // 180 degree or west position of servo motor

Adafruit_PWMServoDriver pwmRight = Adafruit_PWMServoDriver(PCA9685ServoDriver1); // Right servo motor driver object.
Adafruit_PWMServoDriver pwmLeft = Adafruit_PWMServoDriver(PCA9685ServoDriver2); // Left servo motor driver object.
uint8_t phase; // Servo position tracking variable.
uint8_t leg1Hip = 0; // Pin row that motor is connected to.
uint8_t leg2Hip = 3; // Pin row that motor is connected to.
uint8_t leg3Hip = 6; // Pin row that motor is connected to.
uint16_t pwmClkStart = 0; // Start value of count-up PWM high signal.
uint32_t oscFreq = 27000000; // Frequency of oscilator on motor driver. 

/**
 * @brief Initialize serv motor control.
 * ==========================================================================*/
void initServo() 
{
   Serial.println("<initServo> Servo connectivity test.");
   Wire.begin(I2C_BUS0_SDA, I2C_BUS0_SCL, I2C_bus0_speed);
   pwmRight.begin();
   pwmRight.setOscillatorFrequency(oscFreq);
   pwmRight.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
   delay(10);
   pwmLeft.begin();
   pwmLeft.setOscillatorFrequency(oscFreq);
   pwmLeft.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
   delay(10);
   phase = 0; // Start with Servo in the middle
} // initServo()

/**
 * @brief Basic test routing for servo motors.
 * ==========================================================================*/
void updatePhase() 
{
   switch (phase) 
   {
      case 0:
         Serial.println("<loop> phase 0 point north.");
         pwmRight.setPWM(leg1Hip, pwmClkStart, north);  // North position
         pwmRight.setPWM(leg2Hip, pwmClkStart, north);  // North position
         pwmRight.setPWM(leg3Hip, pwmClkStart, north);  // North position
//         pwmLeft.setPWM(leg1Hip, pwmClkStart, north);  // North position
//         pwmLeft.setPWM(leg2Hip, pwmClkStart, north);  // North position
//         pwmLeft.setPWM(leg3Hip, pwmClkStart, north);  // North position
         phase ++;
         break;
      case 1:
         Serial.println("<loop> phase 1 point east.");
         pwmRight.setPWM(leg1Hip, pwmClkStart, east);  // East position
         pwmRight.setPWM(leg2Hip, pwmClkStart, east);  // East position
         pwmRight.setPWM(leg3Hip, pwmClkStart, east);  // East position
//         pwmLeft.setPWM(leg1Hip, pwmClkStart, east);  // East position
//         pwmLeft.setPWM(leg2Hip, pwmClkStart, east);  // East position
//         pwmLeft.setPWM(leg3Hip, pwmClkStart, east);  // East position
         phase ++;
         break;
      case 2:
         Serial.println("<loop> phase 2 point north.");
         pwmRight.setPWM(leg1Hip, pwmClkStart, north);  // North position
         pwmRight.setPWM(leg2Hip, pwmClkStart, north);  // North position
         pwmRight.setPWM(leg3Hip, pwmClkStart, north);  // North position
//         pwmLeft.setPWM(leg1Hip, pwmClkStart, north);  // North position
//         pwmLeft.setPWM(leg2Hip, pwmClkStart, north);  // North position
//         pwmLeft.setPWM(leg3Hip, pwmClkStart, north);  // North position
         phase ++;
         break;
      default:
         Serial.println("<loop> phase 3 point west.");
         pwmRight.setPWM(leg1Hip, pwmClkStart, west);  // West position
         pwmRight.setPWM(leg2Hip, pwmClkStart, west);  // West position
         pwmRight.setPWM(leg3Hip, pwmClkStart, west);  // West position
//         pwmLeft.setPWM(leg1Hip, pwmClkStart, west);  // West position
//         pwmLeft.setPWM(leg2Hip, pwmClkStart, west);  // West position
//         pwmLeft.setPWM(leg3Hip, pwmClkStart, west);  // West position
         phase = 0;
         break;
   } //  switch
} // updatePhase()

#endif // End of precompiler protected code block