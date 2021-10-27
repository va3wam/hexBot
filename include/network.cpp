/*******************************************************************************
 * @file network.cpp  
 * @brief File containing all wifi functions.
 *******************************************************************************/
#ifndef network_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define network_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

/**
 * @brief Initialize Wifi and MQTT.
 * ==========================================================================*/
void setupNetwork()
{
   network.connect(); // Start WiFi connection.
   if(network.areWeConnected() == true) // If we are on the WiFi network.
   {
      networkConnected = true;
      Log.noticeln("<setupNetwork> Connection to network successfully estabished.");
      Log.verboseln("<setupNetwork> Initialize local web services."); 
      startWebServer(); // Start up web server.
      Log.verboseln("<setupNetwork> Initialize MQTT broker connection."); 
      bool tmp = connectToMqttBroker(network); // Connect to MQTT broker.
      if(tmp == true) // If we found an MQTT broker.
      {
         mqttBrokerConnected = true;
         Log.noticeln("<setupNetwork> Connection to MQTT broker successfully established.");
      } // if
      else // If we did not find a valid MQTT broker.
      {
         mqttBrokerConnected = false;
         Log.errorln("<setupNetwork> Connected to MQTT broker failed.");
      } // else
   } // if
   else // If we are NOT on the WiFi network.
   {
      networkConnected = false;
      Log.errorln("<setupNetwork> Not connencted to the network. No MQTT or web interface.");
   } // else
} // setupNetworkNetwork()

#endif // End of precompiler protected code block