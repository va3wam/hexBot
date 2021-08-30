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
#define serialBaudRate 115200 // Serial terminal baud rate.

/**
 * @brief Initialize the serial output.
 * ==========================================================================*/
void setupSerial()
{
   Serial.begin(serialBaudRate); // Open a serial at specified baud rate. 
   while (!Serial); // Wait for Serial port to be ready.
} //setupSerial()

/** 
 * @brief Show the environment details of this application.
 * =================================================================================*/
void showCfgDetails()
{
   Serial.println("<showCfgDetails> Robot Configuration Report");
   Serial.println("<showCfgDetails> ==========================");
   appCpu.cfgToConsole(); // Display core0 information on the console.
   network.cfgToConsole(); // Display network information on the console.
} //showCfgDetails()

/** 
 * @brief Start up the web server.
 * @details Web server supports configuring the MQTT broker IP without needing to 
 *          rebuild. It also provides a web interface for doing OTA code downloads.
 * =================================================================================*/
void startWebServer()
{
   char uniqueName[HOST_NAME_SIZE]; // Contain unique name for Wifi network purposes. 
   char *uniqueNamePtr = &uniqueName[0]; // Pointer to starting address of name. 
   network.getUniqueName(uniqueNamePtr); // Get unique name. 
   Serial.print("<startWebServer> Unique Name: "); Serial.println(uniqueName);
   Serial.print("<startWebServer> Name length: "); Serial.println(strlen(uniqueName));
   isWebServer = localWebService.start(uniqueNamePtr); // Start web server and track result.
   if(isWebServer)
   {
      Serial.println("<startWebServer> Web server successfully started.");
   } //if
   else
   {
      Serial.println("<startWebServer> Web server failed to start.");
   } //else
} //startWebServer()

/**
 * @brief Monitor local web service to see if there are any client requests.
 * @details Call to checkForClientRequest() does two things. First, it causes the 
 * localWebServer service to process any new binay downloads. Second, it returns a 
 * boolean, that when TRUE, indicates there is a new IP address for the MQTT broker 
 * that needs to be saved to NV RAM.
 * =================================================================================*/
void monitorWebServer()
{
   if(localWebService.checkForClientRequest()) // New binary or broker IP?
   {
      IPAddress tmpIP = localWebService.getBrokerIP(); // Get awaiting IP address.
      Serial.print("<monitorWebServer> Set broker IP to "); Serial.println(tmpIP);
      flash.writeBrokerIP(tmpIP); // Write address to flash.
   } //if
} //monitorWebServer()

/**
 * @brief Standard Arduino initialization routine.
 * ==========================================================================*/
void setup() 
{
   setupSerial(); // Set serial baud rate. 
   Serial.println("<setup> Start of setup.");  
   network.connect(); // Start WiFi connection. 
   startWebServer(); // Start up web server.
   showCfgDetails(); // Show all configuration details.

   brokerIP = flash.readBrokerIP(); // Retrieve MQTT broker IP address from NV-RAM.
   Serial.print("<setup> MQTT broker IP believed to be ");
   Serial.println(brokerIP);

   network.getUniqueName(uniqueNamePtr); // Puts unique name value into uniqueName[]
   Serial.print("<setup> Hexbot unique name = ");
   Serial.println(uniqueName);

//   Serial.print("<setup> Ping of broker at "); Serial.print(brokerIP);
//   Serial.print(" resulted in ");
//   Serial.println(network.pingIP(brokerIP, 5));
//   mqtt.connect(brokerIP, uniqueName);
//   bool x = false;
//   while(x == false)
//   {
//      x = mqtt.publishMQTT(HEALTH_MQTT_TOPIC, "This is a test message");
//      delay(1);
//   } //while  
   Serial.println("<setup> End of setup.");   
} // setup()

/**
 * @brief Standard Arduino main loop.
 * ==========================================================================*/
void loop() 
{
   if(localWebService.connectStatus()) // Is there is a valid WiFi connection?
   {
      monitorWebServer(); // Handle any pending web client requests. 
   } //if     
} // loop()  