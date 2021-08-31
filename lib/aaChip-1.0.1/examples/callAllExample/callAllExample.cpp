/******************************************************************************
 * @file callAllExample.cpp
 *
 * @page Example sketch showing how to use the aaChip class. 
 * 
 * @section intro_sec Introduction
 *
 * This is an example sketch provided with the aaChip library that shows how
 * to call all of the functions avaiable via this class and send the 
 * information to the serial console.
 *
 * @section dependencies Dependencies
 * 
 * This sketch class depends on on the following libraries:
 * * <a href="https://github.com/espressif/arduino-esp32">Arduino.h</a>. This 
 * is the Arduino core library that comes bundled with PlatformIO.
 * * <a href="https://github.com/theAgingApprentice/aaChip">aaChip.h</a>. This 
 * is one of the Aging Apprentice's libraries. It exposes information about the 
 * microprocessor that is hosting the firmware. 
 *
 * @section author Author(s)
 *
 * Written by Old Squire for the Aging Apprentice.
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
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <aaChip.h> // Required for retrieving CPU details.

/**
 * Define global objects.
 * =================================================================================*/
aaChip appCore; // Instantiate the aaChip object.

/**
 * @brief Initialize the serial output with the specified baud rate measured in bits 
 * per second.
 * =================================================================================*/
void setupSerial()
{
   unsigned long serialBaudRate = 115200; // Speed we want for serial output (bps).
   Serial.begin(serialBaudRate); // Open a serial connection at specified baud rate. 
   while (!Serial); // Wait for Serial port to be ready.
} //setupSerial()

/**
 * @brief Send detailed chip configuration information to the console.
 * @details The ESP32-D0WDQ6 chip has dual Tensilica LX6 micro controllers. All WiFi 
 * logic runs on the PRO_CPU (core0) aka the processor core. This Arduino firmware 
 * runs on the APP_CPU (core1) aka the application core. 
 * @note: From https://esp32.com/viewtopic.php?t=8558 - The initial design for the 
 * ESP32 called for an asymmetric multiprocessor setup, with CPU0 running all the 
 * PROtocol handling code, while the APPlication would run on CPU1. We changed that to 
 * a symmetric multiprocessor setup later on, and at the moment the two CPUs are (with 
 * very few small exceptions) fully inter-exchangable, and the PRO and APP names are 
 * nothing but some names remaining from the earlier design.      
 * ==================================================================================*/
void cfgToConsole()
{
   Serial.println("<cfgToConsole> Microprocessor information:");  
   Serial.print("<cfgToConsole> ... Chip model = "); 
   Serial.println(appCore.getChipModel()); 
   Serial.print("<cfgToConsole> ... Chip revision = "); 
   Serial.println(appCore.getChipRevision()); 
   Serial.print("<cfgToConsole> ... Arduino core = "); 
   Serial.println(appCore.getCpuId());
   Serial.print("<cfgToConsole> ... Arduino core clock frequency = "); 
   Serial.print(appCore.getCpuClock()); Serial.println(" MHz");
   Serial.print("<cfgToConsole> ... SDK version = "); 
   Serial.println(appCore.getSDKVer()); 
   Serial.print("<cfgToConsole> ... Sketch size = "); 
   Serial.print(appCore.getCodeSize()); Serial.println(" bytes");  
   Serial.print("<cfgToConsole> ... Free heap = "); 
   Serial.print(appCore.getFreeHeap()); Serial.println(" bytes"); 
   Serial.print("<cfgToConsole> ... Serial baud rate = "); 
   Serial.print(appCore.getSerialSpeed()); Serial.println(" Hz");
} //cfgToConsole()

/** 
 * @brief Arduino mandatory function #1. Runs once at boot. 
 * =================================================================================*/
void setup()
{
   setupSerial(); // Sonfigure serial port.
   cfgToConsole(); // Dump info about the processor Arduino is runing on.
} //setup()

/**
 * @brief Arduino mandatory function #2. Runs continually.
 * =================================================================================*/
void loop()
{

} //loop()