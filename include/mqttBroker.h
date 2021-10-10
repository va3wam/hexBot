#ifndef connectToMqttBroker_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define connectToMqttBroker_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.
#include <configDetails.h> // Wifi functions. 
#include <aaStringQueue.h> // Required for string buffer to hold incoming commands.
#include <aaFormat.h> //

aaFlash flash; // Non-volatile memory management. 
aaMqtt mqtt; // Publish and subscribe to MQTT broker. 
IPAddress brokerIP; // IP address of the MQTT broker.
char uniqueName[HOST_NAME_SIZE]; // Character array that holds unique name for Wifi network purposes. 
char *uniqueNamePtr = &uniqueName[0]; // Pointer to first address position of unique name character array.
char healthTopicTree[50] = ""; // Char array to hold full health topic tree name.
String result[2] = {"false","true"}; // Provide english lables for true and flase return codes.

// TODO #7 : A pingable but non MQTT IP address crash loops code.
/** 
 * @brief Establish connect to the the MQTT broker.
 * @details Retrieve the MQTT broker IP address from Flash memory and ping that 
 *          address to see if there is a responsive device on the network. If there 
 *          is then publish a health message noting that end-to-end network services 
 *          are working. Note that upon connecting to the broker the MQTT library 
 *          automatically subscribes to the <unique name>/commands topic.  
 * =================================================================================*/
bool connectToMqttBroker(aaNetwork &network)
{
   network.getUniqueName(uniqueNamePtr); // Puts unique name value into uniqueName[]
   Log.noticeln("<connectToMqttBroker> Hexbot unique network name = %s", uniqueName);
//   Serial.print("<connectToMqttBroker> Hexbot unique network name = ");
//   Serial.println(uniqueName);

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

/**
 * @brief Process the incoming command.
 * =================================================================================*/
bool processCmd(String payload)
{
   aaFormat format;
   String ucPayload = format.stringToUpper(payload);
   const int8_t maxArg = 20; // Allow 1 cmd and up to 19 args in an MQTT message.
   String arg[maxArg]; // arg[0] = cmd, arg[1] = 1st argument, arg[2] = second ...
   int argN = 0; // argument number that we're working on
   int argStart = 0; // character number where current argument starts
   int argEnd = ucPayload.indexOf(",",argStart);  // position of comma at end of cmd
   // Parse comma delimited message into array elements 
   while(argEnd >= 0) // .indexOf returns -1 if no string found
   {  arg[argN] = ucPayload.substring(argStart,argEnd);  // extract the current argument
      argN ++ ; // advance the argument counter
      argStart = argEnd + 1; // next arg starts after previous arg's delimiting comma
      argEnd = ucPayload.indexOf(",",argStart); // find next arg's delimiting comma
   } // while            
   arg[argN] = ucPayload.substring(argStart,argEnd); // last argument has no comma 
                                                     // delimiter. argN ends up as a 
                                                     // count of the number of 
                                                     // arguments, excluding the command

   String cmd = arg[0]; // first comma separated value in payload is the command
   if(cmd == "TEST")
   {
      Serial.println("<processCmd> Recieved test command."); 
      return true;
   }  // if 

   Serial.println("<processCmd> Warning - unrecognized command."); 
   return false;
} // processCmd()

/** 
 * @brief Return the MQTT broker IP address.
 * =================================================================================*/
IPAddress getMqttBrokerIP()
{
   return brokerIP;
} // getMqttBrokerIP()

/** 
 * @brief Check to see if any MQTT commands have come in from the broker.
 * =================================================================================*/
void checkMqtt()
{
   String cmd = mqtt.getCmd();
   if(cmd != "")
   {
      Serial.print("<checkMqtt> cmd = ");
      Serial.println(cmd);
      bool allIsWell = processCmd(cmd);
      if(allIsWell)
      {
         Serial.println("<checkMqtt> All went well.");
      } // if 
      else
      {
         Serial.println("<checkMqtt> Something went wrong.");
      } // if 
   } // if   
} // checkMqtt()

#endif // End of precompiler protected code block