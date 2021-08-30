/******************************************************************************
 * @file aaNetwork.cpp
 *
 * @mainpage the Aging Apprentice wifi management class 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that manages the wifi connection to an Access 
 * Point. This is part of a series of classes made to support a standard set 
 * of APIs for robot platforms. 
 *
 * @section dependencies Dependencies
 * 
 * This class depends on on the following libraries being present on your 
 * system:
 * 1. <a href="https://github.com/espressif/arduino-esp32">Arduino.h</a> 
 * This is the Arduino core library that comes bundled with PlatformIO.
 * 2. <a href="https://github.com/marian-craciunescu/ESP32Ping">ESP32Ping.h</a>
 * Allows you to verify if an IP address can be reached over wifi.
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
#include <aaNetwork.h> // Header file for linking.

/**
 * @class Write variables to flash memory.
 ============================================================================*/
aaNetwork::aaNetwork() 
{
   Serial.println("<aaNetwork::aaNetwork> Default constructor running.");
   _HOST_NAME_PREFIX = "";
} // aaNetwork::aaNetwork()

/**
 * @class Write variables to flash memory.
 * @param const char* Prefix added to the unique network ID for this device.
 ============================================================================*/
aaNetwork::aaNetwork(const char* prefix) 
{
   Serial.println("<aaNetwork::aaNetwork> Default constructor running.");
   _HOST_NAME_PREFIX = prefix;
} // aaNetwork::aaNetwork()

/**
 * @brief This is the destructor for this class.
 =============================================================================*/
aaNetwork::~aaNetwork() 
{
   Serial.println("<aaNetwork::aaNetwork> Destructor running.");
} // aaNetwork::aaNetwork()

/**
 * @brief Report the status of the wifi connection.
 * @return bool true when connected, false when any other status.
 =============================================================================*/
bool aaNetwork::areWeConnected()
{ 
   if(WiFi.status() == WL_CONNECTED)
   {
      return true;
   } // if
   else
   {
      return false;
   } // else
} // aaNetwork::areWeConnected()

/**
 * @brief Construct a name that is sure to be unique on the network.
 * @param char* Pointer to name variable in main.
 =============================================================================*/
void aaNetwork::getUniqueName(char *ptrNameArray)
{ 
   String macAdd = WiFi.macAddress(); // Get MAC address as String
   const char* myMacChar; // Pointer to char array containing the SOC MAC address.   
   const int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses.
   byte myMacByte[macNumBytes]; // Byte array containing the 6 bytes of the SOC Mac address.
   myMacChar = macAdd.c_str(); // Convert to pointer to const char array   
   _convert.macToByteArray(myMacChar, myMacByte); // Convert to Byte array
   _convert.joinTwoConstChar(_HOST_NAME_PREFIX, _convert.noColonMAC(macAdd), _uniqueNamePtr);
   strcpy(ptrNameArray, _uniqueName); // Copy unique name to variable pointer from main.
} // aaNetwork::getUniqueName()

/**
 * @brief Provide human readable text for wifi connection status codes.
 * @param wl_status_t wifi connection status code.
 =============================================================================*/
const char* aaNetwork::_connectionStatus(wl_status_t status)
{
   switch(status) 
   {
      case WL_NO_SHIELD: return "WL_NO_SHIELD"; // For WiFi Shield library.
      case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
      case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
      case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
      case WL_CONNECTED: return "WL_CONNECTED";
      case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
      case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
      case WL_DISCONNECTED: return "WL_DISCONNECTED";
      default: return "UNKNOWN_STATUS";
   } //switch
} // aaNetwork::_connectionStatus()
 
/**
 * @brief Send wifi connection details to console.
 * @param wl_status_t wifi connection status code.
 =============================================================================*/
void aaNetwork::cfgToConsole()
{
   wifi_auth_mode_t encryption = WiFi.encryptionType(_SSIDIndex);
   int8_t dataReadings = 10; // Number of data readings to average to determine Wifi signal strength.
   long signalStrength = rfSignalStrength(dataReadings); // Get average signal strength reading.
   Serial.println("<aaNetwork::cfgToConsole> Network settings:");  
   Serial.print("<aaNetwork::cfgToConsole> ... Access Point Name = "); Serial.println(WiFi.SSID()); 
   Serial.print("<aaNetwork::cfgToConsole> ... Access Point Encryption method = "); Serial.print(encryption,HEX);
   Serial.print(" ("); Serial.print(_translateEncryptionType(WiFi.encryptionType(encryption))); Serial.println(")"); 
   Serial.print("<aaNetwork::cfgToConsole> ... Wifi signal strength = "); Serial.print(signalStrength);
   Serial.print(" ("); Serial.print(evalSignal(signalStrength)); Serial.println(")"); 
   String macAdd = WiFi.macAddress(); // Get MAC address as String
   const int8_t macNumBytes = 6; // MAC addresses have 6 byte addresses.
   byte myMacByte[macNumBytes]; // Byte array containing the 6 bytes of the SOC Mac address.
   const char* myMacChar = WiFi.macAddress().c_str();  
   _convert.macToByteArray(myMacChar, myMacByte); // Convert to Byte array
   Serial.print("<aaNetwork::cfgToConsole> ... Robot MAC address: ");
   Serial.printf("%02X",myMacByte[0]);    
   Serial.print(":");
   Serial.printf("%02X",myMacByte[1]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[2]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[3]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[4]);
   Serial.print(":");
   Serial.printf("%02X",myMacByte[5]);
   Serial.println();
   Serial.print("<aaNetwork::cfgToConsole> ... Robot IP address: "); 
   const char* myIpChar = _convert.ipToString(WiFi.localIP()).c_str(); // Pointer to char array containing MQTT broker IP address
   const int8_t ipv4NumBytes = 4; // IPv4 has 4 byte address 
   byte myIpByte[ipv4NumBytes]; // Byte array for IP address   
   _convert.ipToByteArray(myIpChar, myIpByte); // Convert to byte array
   Serial.print(myIpByte[0],DEC);
   Serial.print(".");
   Serial.print(myIpByte[1],DEC);
   Serial.print(".");
   Serial.print(myIpByte[2],DEC);
   Serial.print(".");
   Serial.println(myIpByte[3],DEC); 
   getUniqueName(_uniqueNamePtr); 
   Serial.print("<aaNetwork::cfgToConsole> ... Robot Host Name: "); Serial.println(_uniqueName);
} // aaNetwork::cfgToConsole()

/**
 * @brief Connect to Wifi.
 =============================================================================*/
void aaNetwork::connect()
{
   if(_lookForAP() == _unknownAP) // Scan the 2.4Ghz band for known Access Points and select the one with the strongest signal 
   {
      Serial.println("<aaNetwork::connect> No known Access Point SSID was detected. Cannot connect to WiFi at this time.");
   } // if
   else // Found a known Access Point to connect to
   {
      WiFi.onEvent(_wiFiEvent); // Set up WiFi event handler
      WiFi.begin(_ssid, _password); // Connect too strongest AP found
      Serial.print("<aaNetwork::connect> Attempting to connect to Access Point with the SSID ");
      Serial.println(_ssid);
      while(WiFi.waitForConnectResult() != WL_CONNECTED) // Hold boot process here until IP assigned
      {
         delay(500);
      } //while
      Serial.println("");
      Serial.print("<aaNetwork::connect> Connected to Access Point with the SSID ");
      Serial.print(_ssid);
      Serial.print(" with status code "); 
      Serial.print(WiFi.status());
      Serial.print(" (");
      Serial.print(_connectionStatus(WiFi.status())); 
      Serial.println(")"); 
   } //else
} // aaNetwork::connect()

/**
 * @brief Collect an average WiFi signal strength. 
 * @param int8_t Number of datapoints to use to create average. 
 * @return long Average signal strength of AP connection in decibels (db).
 =============================================================================*/
long aaNetwork::rfSignalStrength(int8_t dataPoints)
{
   long rssi = 0;
   long averageRSSI = 0;
   for(int i=0; i < dataPoints; i++)
   {
      rssi += WiFi.RSSI();
      delay(20);
   } //for
   averageRSSI = rssi / dataPoints;
   return averageRSSI;
} // aaNetwork::rfSignalStrength()

/**
 * @brief Return human readable assessment of signal strength.
 * @param int16_t Signal strength as measured in decibels (db). 
 * @return const char* Assessment of signal quality in one or two words.
 =============================================================================*/
const char* aaNetwork::evalSignal(int16_t signalStrength)
{
   if(signalStrength <= unusable) return "Unusable";
   if(signalStrength <= notGood) return "Not good";
   if(signalStrength <= okay) return "Okay";
   if(signalStrength <= veryGood) return "Very Good";
   return "Amazing";
} // aaNetwork::evalSignal()

/**
 * @brief Ping IP address once and return the response.
 * @param IPAddress Address to ping. 
 * @return bool Result of ping. 
 =============================================================================*/
bool aaNetwork::pingIP(IPAddress address)
{
   int8_t numPings = 1; // How many pings to send to verify IP address
   IPAddress tmpIp; 
   return Ping.ping(address, numPings);
} // aaNetwork::pingIP()

/**
 * @brief Ping IP address usert specified number of times and return response.
 * @param IPAddress Address to ping. 
 * @param int8_t Number of times to ping address. 
 * @return bool Result of pings. 
 =============================================================================*/
bool aaNetwork::pingIP(IPAddress address, int8_t numPings)
{
   IPAddress tmpIp; 
   return Ping.ping(address, numPings);
} // aaNetwork::pingIP()

/**
 * @brief Scan 2.4GHz radio spectrum for known Access Point.
 * @return const char* Service Set IDentifier (SSID). 
 =============================================================================*/
const char* aaNetwork::_lookForAP()
{
   Serial.println("<aaNetwork::_lookForAP> Scanning the 2.4GHz radio spectrum for known Access Points.");
   _ssid = _unknownAP; //  At the start no known Access Point has been foundto connect to
   int numberOfNetworks = WiFi.scanNetworks(); // Used to track how many APs are detected by the scan
   int StrongestSignal = -127; // Used to find the strongest signal. Set as low as possible to start
   bool APknown; // Flag to indicate if the current AP appears in the known AP list
   Serial.println(numberOfNetworks);

   // Loop through all detected APs
   for(int i = 0; i < numberOfNetworks; i++)
   {
      APknown = false;
   
      // Scan table of known APs to see if the current AP is known to us
      for (int j = 0; j < numKnownAPs; j++)
      {
         // If the current scanned AP appears in the known AP list note the index value and flag found
         if(WiFi.SSID(i) == SSID[j])
         {
            APknown = true;
            _SSIDIndex = j;
         } //if
      }   //for

      // If the current AP is known and has a stronger signal than the others that have been checked
      // then store it in the variables that will be used to connect to the AP later
      if((APknown == true) && (WiFi.SSID(i).toInt() > StrongestSignal))
      {
         _ssid = SSID[_SSIDIndex].c_str();
         _password = Password[_SSIDIndex].c_str();
         StrongestSignal = WiFi.SSID(i).toInt();
      } //if
   } //for
   return _ssid;
} // aaNetwork::_lookForAP()

/**
 * @brief Provide human readable wifi encryption method.
 * @param wifi_auth_mode_t Wifi encryption type code.
 * @return const char* Encryption type in one word. 
 =============================================================================*/
const char* aaNetwork::_translateEncryptionType(wifi_auth_mode_t encryptionType)
{
   switch (encryptionType)
   {
      case (WIFI_AUTH_OPEN): return "Open";
      case (WIFI_AUTH_WEP): return "WEP";
      case (WIFI_AUTH_WPA_PSK): return "WPA_PSK";
      case (WIFI_AUTH_WPA2_PSK): return "WPA2_PSK";
      case (WIFI_AUTH_WPA_WPA2_PSK): return "WPA_WPA2_PSK";
      case (WIFI_AUTH_WPA2_ENTERPRISE): return "WPA2_ENTERPRISE";
      default: return "UNKNOWN";
   } //switch
} // aaNetwork::_translateEncryptionType()

/**
 * @brief Event handler for wifi.
 * @details Tracks all wifi event activity even though we do not act on any of 
 * it at this time. At the very least the logs help us trouble shoot wifi issues 
 * but this routine also acts as a reminder of what functional possibilities 
 * exist for future consideration.
 * @param WiFiEvent_t Type of event that triggered this handler.
 * @param WiFiEventInfo_t Additional information about the triggering event.
 =============================================================================*/
void aaNetwork::_wiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info)
{
   switch(event) 
   {
      case SYSTEM_EVENT_AP_START:
//         WiFi.softAP(AP_SSID, AP_PASS); //can set ap hostname here   
//         WiFi.softAPenableIpV6(); //enable ap ipv6 here
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_AP_START");            
         break;
      case SYSTEM_EVENT_STA_START:         
//         WiFi.setHostname(AP_SSID); //set sta hostname here
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_START");            
         break;
      case SYSTEM_EVENT_STA_CONNECTED:         
//         WiFi.enableIpV6(); //enable sta ipv6 here
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_CONNECTED");            
         break;
      case SYSTEM_EVENT_AP_STA_GOT_IP6:
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_AP_STA_GOT_IP6");            
         break;
      case SYSTEM_EVENT_STA_GOT_IP:
//         wifiOnConnect(); // Call function to do things dependant upon getting wifi connected
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_GOT_IP");            
         break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
         Serial.println("<aaNetwork::WiFiEvent> Detected SYSTEM_EVENT_STA_DISCONNECTED");            
         break;
      case WL_NO_SSID_AVAIL:
         Serial.println("<aaNetwork::WiFiEvent> WL_NO_SSID_AVAIL");            
         break;
      case WL_IDLE_STATUS: 
         Serial.println("<aaNetwork::WiFiEvent> Detected WL_IDLE_STATUS");            
         break;
      default:
         Serial.println("<aaNetwork::WiFiEvent> ERROR - UNKNOW SYSTEM EVENT"); 
         Serial.print("<aaNetwork::WiFiEvent> ... Event = "); Serial.println(event);           
         break;
   } //switch
} // aaNetwork::_wiFiEvent()