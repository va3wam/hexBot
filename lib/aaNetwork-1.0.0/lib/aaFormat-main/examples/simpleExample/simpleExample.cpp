/******************************************************************************
 * @file simpleExample.cpp
 *
 * @page Example sketch showing how to use the aaFormat class. 
 * 
 * @section intro_sec Introduction
 *
 * This is an example sketch provided with the aaFormat library that shows how
 * to perform various data type conversions and other formatting stuff.
 *
 * @section dependencies Dependencies
 * 
 * This sketch class depends on on the following libraries:
 * - <a href="https://github.com/espressif/arduino-esp32">Arduino.h</a>. This 
 * is the Arduino core library that comes bundled with PlatformIO.
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
#include <aaFormat.h> // Store values that persist past reboot.

/**
 * Define global objects.
 * =================================================================================*/
aaFormat convert; // Explain what this object reference is for. 

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
 * @brief Show how to set up and call MAC address formatting functions. 
 * =================================================================================*/
void exampleMacStuff()
{
   String macAdd = "12:34:56:78:9A:BC"; // Mock-up of MAC address.
   const char* myMacChar; // Pointer to char array that will hold MAC address.   
   const int8_t macNumBytes = 6; // MAC addresses have 6 bytes.
   byte myMacByte[macNumBytes]; // Byte array containing the 6 bytes MAC address.
   myMacChar = macAdd.c_str(); // Convert to pointer to const char array.   
   convert.macToByteArray(myMacChar, myMacByte); // Convert to Byte array.
   Serial.print("<exampleMacStuff> myMacByte = ");
   Serial.print(myMacByte[0], HEX);
   Serial.print(myMacByte[1], HEX);
   Serial.print(myMacByte[2], HEX);
   Serial.print(myMacByte[3], HEX);
   Serial.print(myMacByte[4], HEX);
   Serial.println(myMacByte[5], HEX);
} // exampleMacStuff()

/** 
 * @brief Show how to set up and call IP address formatting functions. 
 * =================================================================================*/
void exampleIpStuff()
{
   // Demonstrate how to concatinate two char* and how to parse a MAC address.
   const char* HOST_NAME_PREFIX = "EXAMPLE"; // Mock-up network name prefix.
   const char* macAdd = "12:34:56:78:9A:BC"; // Mock-up of MAC address.
   int8_t maxSizeName = 30; // Length of name.
   char exampleName[maxSizeName]; // char array to hold name.
   char* uniqueNamePtr = exampleName; // Pointer to char array. 
   convert.joinTwoConstChar(HOST_NAME_PREFIX, convert.noColonMAC(macAdd), uniqueNamePtr);
   Serial.print("<exampleIpStuff> Concatinated unique name = ");
   Serial.println(exampleName);

   // Demonstrate how to parse an IP address.
   String ipAdd = "111.112.113.114"; // Mock-up of IP address.
   const char* myIpChar; // Pointer to char array that will hold IP address.   
   const int8_t ipNumBytes = 4; // IP addresses have 4 bytes.
   byte myIpByte[ipNumBytes]; // Byte array containing the 4 bytes IP address.
   myIpChar = ipAdd.c_str(); // Convert to pointer to const char array.   
   convert.ipToByteArray(myIpChar, myIpByte); 
   Serial.print("<exampleIpStuff> myIpByte = ");
   Serial.print(myIpByte[0]);
   Serial.print(".");
   Serial.print(myIpByte[1]);
   Serial.print(".");
   Serial.print(myIpByte[2]);
   Serial.print(".");
   Serial.println(myIpByte[3]);
} // exampleIpStuff()

/** 
 * @brief Show how to use the generic string formatting functions.
 * =================================================================================*/
void exampleStringStuff()
{
   // Demonstrate how to make a String all upper case.
   String lowercaseString = "this started out all lower case.";
   Serial.print("<exampleStringStuff> Before conversion: ");
   Serial.println(lowercaseString);
   String uppercaseString = convert.stringToUpper(lowercaseString);
   Serial.print("<exampleStringStuff> After conversion: ");
   Serial.println(uppercaseString);
} // exampleStringStuff()

/** 
 * @brief Arduino mandatory function #1. Runs once at boot. 
 * =================================================================================*/
void setup()
{
   setupSerial(); // Set serial baud rate. 
   Serial.println("<setup> Start of setup");
   exampleMacStuff(); // Do MAC address formatting stuff.
   exampleIpStuff(); // Do IP address formatting stuff.
   exampleStringStuff(); // STring manipulations. 
   Serial.println("<setup> End of setup");
} // setup()

/**
 * @brief Arduino mandatory function #2. Runs continually.
 * =================================================================================*/
void loop()
{

} //loop()