/******************************************************************************
 * @file aaFormat.cpp
 *
 * @mainpage the Aging Apprentice data conversion and formatting class. 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that converts data from one type to another typee
 * as well as formatting data. This is part of a series of classes made to 
 * support a standard set of APIs for robot platforms. 
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
#include <aaFormat.h> // Header file for linking.

/**
 * @class Convert between data types and/or format data.
 ============================================================================*/
aaFormat::aaFormat() 
{
   Serial.println("<aaFormat::aaFormat> Default constructor running.");
} // aaFormat::aaFormat()

/**
 * @brief This is the destructor for this class.
 =============================================================================*/
aaFormat::~aaFormat() 
{
   Serial.println("<aaFormat::aaFormat> Destructor running.");
} // aaFormat::aaFormat()

/**
 * @brief Format the devices MAC address.
 * @details Strip the colons out of the MAC address as well as converting it 
 * from String to const char*.
 * @param String MAC address.
 * @return const char* MAC address without colons. 
 =============================================================================*/
const char* aaFormat::noColonMAC(String macAddress)
{
   macAddress.remove(2, 1); // Remove first colon from MAC address
   macAddress.remove(4, 1); // Remove second colon from MAC address
   macAddress.remove(6, 1); // Remove third colon from MAC address
   macAddress.remove(8, 1); // Remove forth colon from MAC address
   macAddress.remove(10, 1); // Remove fifth colon from MAC address
   return macAddress.c_str();
} // aaFormat::noColonMAC()

/**
 * @brief Convert String to all upper case.
 * @param String Sting to be converted.
 * @return String String in  all upper case. 
 =============================================================================*/
String aaFormat::stringToUpper(String strToConvert)
{
   std::transform(strToConvert.begin(), strToConvert.end(), strToConvert.begin(), ::toupper);
   return strToConvert;
} // aaFormat::stringToUpper()

/**
 * @brief Convert IPAddress format to String format.
 * @param IPAddress IP address to be converted.
 * @return String Converted IP address. 
 =============================================================================*/
String aaFormat::ipToString(IPAddress ip)
{
   String s = "";
   for (int i = 0; i < 4; i++)
   {
      s += i ? "." + String(ip[i]) : String(ip[i]);
   } //for
   return s;
} // aaFormat::ipToString()

/**
 * @brief Convert char array containing IP address to byte array.
 * @param const char* IP address to be converted.
 * @param bytes Pointer to byte array into which to place IP address octets. 
 =============================================================================*/
void aaFormat::ipToByteArray(const char* str, byte* bytes)
{
   int8_t ipv4NumBytes = 4; // IPv4 has 4 byte address
   int8_t baseNumberingSystem = 10; // IPv4 uses base 10 for its bytes
   char byteSeperator = '.'; // IP address bytes are seperated with a period
   _parseBytes(str, byteSeperator, bytes, ipv4NumBytes, baseNumberingSystem);
} // aaFormat::ipToByteArray()

/**
 * @brief Convert char array containing MAC address to byte array.
 * @param const char* MAC address to be converted.
 * @param bytes Pointer to byte array into which to place MAC address octets. 
 =============================================================================*/
void aaFormat::macToByteArray(const char* str, byte* bytes)
{
   int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses
   int8_t baseNumberingSystem = 16; // MAC addresses use base 16 for their bytes
   char byteSeperator = ':'; // MAC address bytes are seperated with a dash
   _parseBytes(str, byteSeperator, bytes, macNumBytes, baseNumberingSystem);
} // aaFormat::macToByteArray()

/**
 * @brief Concatinate two const char* arrays in one buffer.
 * @param const char* First array.
 * @param const char* Second array. 
 * @param const char* pointer to target array in main. 
 =============================================================================*/
void aaFormat::joinTwoConstChar(const char *a, const char *b, char *out)
{
   strcpy(out, a);
   strcat(out, b);
} // aaFormat::joinTwoConstChar()

/**
 * @brief Convert char array (ASCII) to byte array.
 * @param const char* .
 * @param char . 
 * @param byte* .
 * @param int8_t . 
 * @param int8_t .  
 =============================================================================*/
void aaFormat::_parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base)
{
   for (int i = 0; i < maxBytes; i++) 
   {
      bytes[i] = strtoul(str, NULL, base); // Convert byte
      str = strchr(str, sep); // Find next separator
      if (str == NULL || *str == '\0') 
      {
         break; // No more separators, exit
      } //if
      str++; // Point to next character after separator
   } //for
} // aaFormat::_parseBytes()