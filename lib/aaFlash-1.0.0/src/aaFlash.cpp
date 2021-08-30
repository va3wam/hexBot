/******************************************************************************
 * @file aaFlash.cpp
 *
 * @mainpage the Aging Apprentice flash memory class 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that saves variables to flash memory to preserve
 * information through a reboot. This is part of a series of classes made 
 * to support a standard set of APIs for robot platforms. 
 *
 * @section dependencies Dependencies
 * 
 * This class depends on on <a href="https://github.com/espressif/arduino-esp32">
 * Arduino.h</a> being present on your system. This is the Arduino core library
 * that comes bundled with PlatformIO.
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
#include <aaFlash.h> // Header file for linking.
Preferences preferences; // Save to flash for variables to persist past reset.
const char* DEFAULT_MQTT_IP = "192.168.0.99"; // Default IP address.
const char* FLASH_APP_NAME = "my_app"; // Argument for flash read.

/**
 * @class Write variables to flash memory.
 * ==========================================================================*/
aaFlash::aaFlash() 
{
   Serial.println("<aaFlash::aaFlash> Default constructor running.");
} //aaFlash::aaFlash()

/**
 * @brief This is the destructor for this class.
=============================================================================*/
aaFlash::~aaFlash() 
{
   Serial.println("<aaFlash::aaFlash> Destructor running.");
} //aaFlash::aaFlash()

/**
 * @brief Read MQTT broker IP address from flash memory.
 * @return IPAddress Value read from flash memory.
=============================================================================*/
IPAddress aaFlash::readBrokerIP()
{
   bool RW_MODE = false;
   IPAddress addrIP; // Broker IP address in String format.
   String addrStr; // Broker IP address in IPAddress format.
   preferences.begin(FLASH_APP_NAME, RW_MODE); // Open flash in read/write mode.
   addrStr = preferences.getString("brokerIP", DEFAULT_MQTT_IP).c_str(); // Read.
   preferences.end(); // Close access to flash memory.
   Serial.print("<aaFlash::readBrokerIP> MQTT Broker IP address in NVRAM = ");
   Serial.println(addrIP);
   // addrIP.fromString(addrStr); // Convert String to IPAddress format.
   return addrIP;
} //aaFlash::readBrokerIP()

/**
 * @brief Write MQTT broker IP address to flash memory.
 * @param IPAddress IP address to be written to flash memory.
=============================================================================*/
void aaFlash::writeBrokerIP(IPAddress address)
{
   bool RW_MODE = false;
   Serial.print("<aaFlash::write> Writing this address to flash memory: ");
   Serial.println(address);
   preferences.begin(FLASH_APP_NAME, RW_MODE); // Open flash in read/write mode.
   preferences.putString("brokerIP", address.toString()); // Write IP address.
   preferences.end(); // Close access to flash memory. 
} //aaFlash::writeBrokerIP()