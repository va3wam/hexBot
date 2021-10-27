/*******************************************************************************
 * @file web.cpp  
 * @brief File containing all local web server functions.
 *******************************************************************************/
#ifndef web_cpp // Start of precompiler check to avoid dupicate inclusion of this code block.

#define web_cpp // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

/**
 * @brief Monitor local web service to see if there are any client requests.
 * @details Call to checkForClientRequest() does two things. First, it causes the 
 * localWebServer service to process any new binay downloads. Second, it returns a 
 * boolean, that when TRUE, indicates there is a new IP address for the MQTT broker 
 * that needs to be saved to NV RAM.
 * =================================================================================*/
void monitorWebServer()
{
   if(localWebService.connectStatus()) // Is there is a valid WiFi connection?
   {
      if(localWebService.checkForClientRequest()) // New binary or broker IP?
      {
         IPAddress tmpIP = localWebService.getBrokerIP(); // Get awaiting IP address.
         Log.noticeln("<monitorWebServer> Set broker IP to %p", tmpIP); 
         flash.writeBrokerIP(tmpIP); // Write address to flash.
         brokerIP = flash.readBrokerIP(); // Retrieve MQTT broker IP address from NV-RAM.
         Log.noticeln("<monitorWebServer> MQTT broker IP believed to be %p", brokerIP);
      } //if
   } //if     
} //monitorWebServer()

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
   Log.noticeln("<startWebServer> Unique Name: %s (Length of %d).", uniqueName, strlen(uniqueName));
   isWebServer = localWebService.start(uniqueNamePtr); // Start web server and track result.
   if(isWebServer)
   {
      Log.noticeln("<startWebServer> Web server successfully started.");
   } //if
   else
   {
      Log.errorln("<startWebServer> Web server failed to start.");
   } //else
} //startWebServer()

#endif // End of precompiler protected code block