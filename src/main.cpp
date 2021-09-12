/******************************************************************************
 * @file main.cpp
 *
 * @mainpage Hexbot firmware. 
 * 
 * @section intro_sec Introduction
 *
 * This code is the firmware for the six legged robot called Hexbot. Full
 * details on how to get the circuit and chassis for this robot are found
 * [here](https://github.com/va3wam/hexBot). 
 *
 * @section dependencies Dependencies
 * 
 * This sketch depends on the libraries located in the main.h file located in
 * the include directory of this repository.
 *
 * @section author Author(s)
 *
 * Written by Old Squire and Doug Elliott.
 *
 * @section license license
 *
 * Copyright 2021 the Aging Apprentice 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions: The above copyright
 * notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.  
 *****************************************************************************/
#include <main.h> // Header file for all libraries needed by this program.
// TODO #4 Address error initialization from incompatible pointer type [-Wincompatible-pointer-types]
// TODO #5 Add I2C support

#include <Wire.h> // I2C communication.
#include <Adafruit_PWMServoDriver.h> // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library.
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, Wire); // I2C address 0x40 (default) on Wire1.
#define SERVO_FREQ 50 // Analog servos run at a freq of 50Hz creating a period of (1/50*1000 = 20ms). 
                      // Can be between 40Hz and 1600Hz. Servo motors tyically use 50Hz.
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED; // Mutex to prevent ISR and main conflicts                      
volatile int interruptCounter = 0; // Number of signals from servo driver not processed.
volatile long last, now; // Track freq of servo motorcontroller PWM signal.
const byte interruptPin = 14; // GPIO14 is physical pin 5 on 30 pin Devkit V1 board.
uint32_t oscFreq = 27000000; // Oscillator freq of the PCA9865 servo motor driver. Board specific.

#define PIN_SERVO_FEEDBACK 15 // Connect white PWM pin, 15 = last on last block. Monitor PWM from servo driver.
int numberOfInterrupts = 0; // Total number of servo driver signals in total.
unsigned long timer; // Milli count for next action.
int32_t cadencePeriod; // How long between phases in millis.
uint8_t leftDriverPinNum = 14; // Target pin on left motor driver.
uint16_t pwmOnCnt = 0; // PWM counter when to raise signal.
uint16_t pwmOffCnt = 300; // PWM counter when to lower signal.

/**
 * @brief ISR for PWM signal from PCA9685.
 * =================================================================================*/
void IRAM_ATTR handleInterrupt() 
{
  portENTER_CRITICAL_ISR(&mux);
  interruptCounter++;
  last = now;
  now = millis();
  portEXIT_CRITICAL_ISR(&mux);
} // handleInterrupt()

/**
 * @brief Standard Arduino initialization routine.
 * ==========================================================================*/
void setup() 
{
   setupSerial(); // Set serial baud rate. 
   Serial.println("<setup> Start of setup.");  
   Wire.begin(I2C_bus0_SDA,I2C_bus0_SCL,I2C_bus0_speed);
   scanBus0();
//   Wire1.begin(I2C_bus1_SDA,I2C_bus1_SCL,I2C_bus1_speed);
//   scanBus1();
   network.connect(); // Start WiFi connection. 
   startWebServer(); // Start up web server.
   showCfgDetails(); // Show all configuration details.
   bool tmp = connectToMqttBroker(); // Connect to MQTT broker.
   Serial.print("<setup> Connected to MQTT broker = ");
   Serial.print(tmp); Serial.print(" ("); Serial.print(result[tmp]); Serial.println(")");
   Serial.println("<setup> End of setup."); 
} // setup()

/**
 * @brief Standard Arduino main loop.
 * ==========================================================================*/
void loop() 
{
   monitorWebServer(); // Handle any pending web client requests. 
   // Check if external PWM interrupt has occured and track with counters.
   if(interruptCounter > 0)
   {
      portENTER_CRITICAL(&mux);
      interruptCounter--;
      portEXIT_CRITICAL(&mux);
      numberOfInterrupts++;
   } // if

   if(timer <= millis()) // Time to act?
   {
      pwm.setPWM(leftDriverPinNum,pwmOnCnt,pwmOffCnt);
      timer = millis() + cadencePeriod;
   } //if
} // loop()  