#ifndef connectToMqttBroker_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define connectToMqttBroker_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

aaFlash flash; // Non-volatile memory management. 
aaMqtt mqtt; // Publish and subscribe to MQTT broker. 
IPAddress brokerIP; // IP address of the MQTT broker.
char uniqueName[HOST_NAME_SIZE]; // Character array that holds unique name for Wifi network purposes. 
char *uniqueNamePtr = &uniqueName[0]; // Pointer to first address position of unique name character array.
char healthTopicTree[50] = ""; // Char array to hold full health topic tree name.

// TODO #7 : A pingable but non MQTT IP address crash loops code.
/** 
 * @brief Establish connect to the the MQTT broker.
 * @details Retrieve the MQTT broker IP address from Flash memory and ping that 
 *          address to see if there is a responsive device on the network. If there 
 *          is then publish a health message noting that end-to-end network services 
 *          are working. Note that upon connecting to the broker the MQTT library 
 *          automatically subscribes to the <unique name>/commands topic.  
 * =================================================================================*/
bool connectToMqttBroker()
{
   network.getUniqueName(uniqueNamePtr); // Puts unique name value into uniqueName[]
   Serial.print("<connectToMqttBroker> Hexbot unique network name = ");
   Serial.println(uniqueName);

   Serial.print("<connectToMqttBroker> Health topic = ");
   Serial.println(HEALTH_MQTT_TOPIC);

   strcpy(healthTopicTree, uniqueName);
   strcat(healthTopicTree, HEALTH_MQTT_TOPIC);

   Serial.print("<connectToMqttBroker> Full health topic tree = ");
   Serial.println(healthTopicTree);

   Serial.print("<connectToMqttBroker> Length of health topic tree = ");
   Serial.println(strlen(healthTopicTree));

   brokerIP = flash.readBrokerIP(); // Retrieve MQTT broker IP address from NV-RAM.
   Serial.print("<connectToMqttBroker> MQTT broker IP believed to be ");
   Serial.println(brokerIP);

   bool tmpPingResult = network.pingIP(brokerIP, 5);
   String tmpResult[2];
   tmpResult[0] = "Not found - invalid address";
   tmpResult[1] = "Found - valid address";
   Serial.print("<connectToMqttBroker> Ping of broker at "); Serial.print(brokerIP);
   Serial.print(" resulted in ");
   Serial.print(tmpPingResult);
   Serial.print(" (");
   Serial.print(tmpResult[tmpPingResult]);
   Serial.println(")");
   if(tmpPingResult == true)
   {
      mqtt.connect(brokerIP, uniqueName);
      bool x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(healthTopicTree, "End-to-end network services estabished");
         delay(1);
      } //while  
   } //if
   else
   {
      Serial.println("<connectToMqttBroker> Cannot reach MQTT broker. Boot halting.");
      return false; 
   } //else
   return true;
} //connectToMqttBroker()

#endif // End of precompiler protected code block