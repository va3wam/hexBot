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
unsigned long timer; // Milli count for next action.

/**
 * @brief Standard Arduino initialization routine.
 * ==========================================================================*/
void setup() 
{
   setupSerial(); // Set serial baud rate. 
   Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
   Log.traceln("<setup> Start of setup."); 
   Log.verboseln("<setup> Initialize I2C buses.");  
   Wire.begin(G_I2C_BUS0_SDA, G_I2C_BUS0_SCL, I2C_BUS0_SPEED); // Init I2C bus0.
   scanBus0(); // Scan bus0 and show connected devices.
   Log.traceln("<setup> Initialize OLED.");
   initOled();
   Log.verboseln("<setup> Initialize status RGB LED."); 
   setupStatusLed(); // Configure the status LED on the reset button.
   setStdRgbColour(WHITE); // Indicates that boot up is in progress.
   Log.verboseln("<setup> Set up wifi connection."); 
   setupNetwork();
   Log.traceln("<setup> Initialize servo drivers.");
   setupMobility();
   Log.verboseln("<setup> Display robot configuration in console trace."); 
   showCfgDetails(); // Show all configuration details in one summary.
   testDaeIKFunctions(); // Doug's IK routines.
   Log.verboseln("<setup> Review status flags to see how boot sequence went."); 
   checkBoot();   
   timer = millis(); // Timer for motor driver signalling.
   Log.traceln("<setup> End of setup."); 
} // setup()

/**
 * @brief Standard Arduino main loop.
 * ==========================================================================*/
void loop() 
{
   monitorWebServer(); // Handle any pending web client requests. 
   checkOledButtons(); // Check if an OLED button has been pressed.
   checkMqtt(); // Check the MQTT message queue for incoming commands.
} // loop()  