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
#include <aaStringQueue.h> // Required for retrieving CPU details.

/**
 * Define global objects.
 * =================================================================================*/
aaStringQueue cmdQueue; // Instantiate the command queue.

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
 * @brief Arduino mandatory function #1. Runs once at boot. 
 * =================================================================================*/
void setup()
{
   char msg1[20] = "msg1";
   char msg2[20] = "msg2";
   char msg3[20] = "msg3";
   char msg4[20] = "msg4";
   char msg5[20] = "msg5";
   char msg6[20] = "msg6";
   char msg7[20] = "msg7";
   char msg8[20] = "msg8";
   setupSerial(); // Set serial baud rate. 
   Serial.println("<setup> Start of setup");
   Serial.println("<setup> Show buffer content before we start.");
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg1);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg2);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg3);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg4);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg5);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg6);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg7);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Add a message to the buffer.");
   cmdQueue.push(msg8);
   cmdQueue.dumpBuffer();
   Serial.println("<setup> Pull a message from the buffer.");
   char str[cmdQueue.getMaxBufferSize()];
   cmdQueue.pop(str);
   cmdQueue.dumpBuffer();
   Serial.print("<setup> myMessage = "); Serial.println(str);
   Serial.println("<setup> Clear the buffer.");
   cmdQueue.flush();
   cmdQueue.dumpBuffer();
   Serial.println("<setup> End of setup");
} // setup()

/**
 * @brief Arduino mandatory function #2. Runs continually.
 * =================================================================================*/
void loop()
{

} //loop()