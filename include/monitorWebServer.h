#ifndef monitorWebServer_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define monitorWebServer_h // Precompiler macro used for precompiler check.

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
         Log.noticeln("<setup> MQTT broker IP believed to be %p", brokerIP);
      } //if
   } //if     
} //monitorWebServer()

#endif // End of precompiler protected code block