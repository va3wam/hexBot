/*************************************************************************************************************************************
 * @file aaFlash.cpp
 * @author theAgingApprentice
 * @brief Store values in flash memory. 
 * @details The ESP32 uses off chip flash memory which retains its values through a reboot.
 * @copyright Copyright (c) 2021 the Aging Apprentice
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
 * (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, 
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished 
 * to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 * 
 * YYYY-MM-DD Dev        Description
 * ---------- ---------- -------------------------------------------------------------------------------------------------------------
 * 2021-03-28 Old Squire Program created.
 *************************************************************************************************************************************/
#include <aaFlash.h> // Header file for linking.
Preferences preferences; // Save to SPI NOR flash for variables to persist past reset
const char* DEFAULT_MQTT_IP = "192.168.0.99";
const char* FLASH_APP_NAME = "my_app";

/**
 * @brief This is the default constructor for this class.
===================================================================================================*/
aaFlash::aaFlash() 
{
   Serial.println("<aaFlash::aaFlash> Default constructor running.");
} //aaFlash::aaFlash()

/**
 * @brief This is the second form of the constructor for this class.
===================================================================================================*/
aaFlash::aaFlash(const char* var1)
{
   Serial.println("<aaFlash::aaFlash> Second form constructor running.");
} //aaFlash::aaFlash()

/**
 * @brief This is the destructor for this class.
===================================================================================================*/
aaFlash::~aaFlash() 
{
   Serial.println("<aaFlash::aaFlash> Destructor running.");
} //aaFlash::aaFlash()

/**
 * @brief Read MQTT broker IP address from flash memory.
 * @return String var String read from flash memory.
===================================================================================================*/
IPAddress aaFlash::readBrokerIP()
{
   bool RW_MODE = false;
   IPAddress addrIP; // Broker IP address in String format.
   String addrStr; // Broker IP address in IPAddress format.
   preferences.begin(FLASH_APP_NAME, RW_MODE); // Open flash memory in read/write mode.
   addrStr = preferences.getString("brokerIP", DEFAULT_MQTT_IP).c_str(); // Read IP address.
   preferences.end(); // Close access to flash memory.
   addrIP.fromString(addrStr); // Convert String to IPAddress format.
   return addrIP;
} //aaFlash::readBrokerIP()

/**
 * @brief Write MQTT broker IP address to flash memory.
 * @param String var String to be written to flash memory.
===================================================================================================*/
void aaFlash::writeBrokerIP(IPAddress address)
{
   bool RW_MODE = false;
   Serial.print("<aaFlash::write> Writing this address to flash memory: ");
   Serial.println(address);
   preferences.begin(FLASH_APP_NAME, RW_MODE); // Open flash memory in read/write mode.
   preferences.putString("brokerIP", address.toString()); // Write IP address.
   preferences.end(); // Close access to flash memory. 
} //aaFlash::writeBrokerIP()