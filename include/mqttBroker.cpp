/*******************************************************************************
 * @file mqttBroker.cpp  
 * @brief File containing all MQTT functions.
 *******************************************************************************/
#ifndef connectToMqttBroker_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define connectToMqttBroker_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

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
   Log.noticeln("<connectToMqttBroker> Hexbot unique network name = %s.", uniqueName);
   Log.noticeln("<connectToMqttBroker> Health topic = %s.", HEALTH_MQTT_TOPIC);
   strcpy(healthTopicTree, uniqueName);
   strcat(healthTopicTree, HEALTH_MQTT_TOPIC);
   Log.noticeln("<connectToMqttBroker> Full health topic tree = %s (length = %d).", healthTopicTree, strlen(healthTopicTree));
   Log.noticeln("<connectToMqttBroker> Help topic = %s.", HELP_MQTT_TOPIC);
   strcpy(helpTopicTree, uniqueName);
   strcat(helpTopicTree, HELP_MQTT_TOPIC);
   Log.noticeln("<connectToMqttBroker> Full help topic tree = %s (length = %d).", helpTopicTree, strlen(helpTopicTree));
   brokerIP = flash.readBrokerIP(); // Retrieve MQTT broker IP address from NV-RAM.
   Log.noticeln("<connectToMqttBroker> MQTT broker IP believed to be %p.", brokerIP);
   bool tmpPingResult = network.pingIP(brokerIP, 5);
   String tmpResult[2];
   tmpResult[0] = "Not found - invalid address";
   tmpResult[1] = "Found - valid address";
   Log.noticeln("<connectToMqttBroker> Ping of broker at %p resulted in %T.", brokerIP, tmpPingResult);
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
      Log.errorln("<connectToMqttBroker> Cannot reach MQTT broker.");
      return false; 
   } //else
   return true;
} //connectToMqttBroker()

/**
 * @brief Check is a string variable is a valid number.
 * @return true if it is a valid number and false if it is not.
 * =================================================================================*/
boolean isValidNumber(String str)
{
   for(byte i=0;i<str.length();i++)
   {
      if(!isDigit(str.charAt(i))) 
      {
         return false;
      } //if
   } // for
   return true;
} // isValidNumber()

/**
 * @brief Converts a string variable to a unit32_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
uint32_t convertStrToUint32_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10); 
   return (uint32_t) numToConvert;  
} // convertStrToUint32_t()

/**
 * @brief Converts a string variable to a uint8_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
uint8_t convertStrToUint8_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10); 
   return (uint8_t) numToConvert;  
} // convertStrToUint8_t()

/**
 * @brief Converts a string variable to a int8_t variable.
 * @param var is the string to be converted.
 * @return The convereted value. 
 * =================================================================================*/
int8_t convertStrToInt8_t(String var)
{
   unsigned long numToConvert = strtoul(var.c_str(), NULL, 10); 
   return (int8_t) numToConvert;  
} // convertStrToInt8_t()

/**
 * @brief Check if command arguments are valid numbers.
 * @param numArgumentsRequired how many numbers are expected.
 * @param argN number of arguments passed by command.
 * @param *arg pointer to array containing the arguments to be checked.
 * @return true if there are the right number of arguments and they are all numbers,
 * false if the number of arguments is wrong or if one of the arguments is not a 
 * number. 
 * =================================================================================*/
bool checkNumArg(int8_t numArgumentsRequired, int argN, String *arg)
{
   if(argN == numArgumentsRequired) // Right number of arguments?
   {
      Log.verboseln("<checkNumArg> Correct number of arguments recieved."); 
      for(int8_t i = 1; i <= numArgumentsRequired; i ++) // Are the three arguments valid numbers. 
      {
         if(isValidNumber(arg[i])) // If current argument is a valid number.
         {
            Log.verboseln("<checkNumArg> arg[%d] = %s and is a valid number.", i, arg[i]); 
         } // if
         else //  If current argument is not a valid number.
         {
            Log.warningln("<checkNumArg> Ignoring command. arg[%d] = %s and is not a valid number.", i, arg[i]);
            return false; 
         } // if
      } // for 
   } // if
   else // Wrong number of arguments
   {
      Log.warningln("<checkNumArg> Ignoring command. SET_CUST_RGB_CLR requires %d arguments but recieved %i.", numArgumentsRequired, argN); 
      return false;
   } // else
   return true;   
} // checkNumArg()

/**
 * @brief Process the incoming command.
 * @param payload Command recieved from MQTT broker.
 * @return True is the command is known. False if the cmmand is unknown.
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
   {  
      arg[argN] = ucPayload.substring(argStart,argEnd);  // extract the current argument
      argN ++ ; // advance the argument counter
      argStart = argEnd + 1; // next arg starts after previous arg's delimiting comma
      argEnd = ucPayload.indexOf(",",argStart); // find next arg's delimiting comma
   } // while            
   arg[argN] = ucPayload.substring(argStart,argEnd); // last argument has no comma 
                                                     // delimiter. argN ends up as a 
                                                     // count of the number of 
                                                     // arguments, excluding the command
   String cmd = arg[0]; // first comma separated value in payload is the command
   // TEST command.
   if(cmd == "TEST")
   {
      Log.noticeln("<processCmd> Recieved test command."); 
      return true;
   }  // if 
   // HELP command.
   if(cmd == "HELP")
   {
      Log.noticeln("<processCmd> Recieved help command."); 
      bool x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "TEST - Issues test message to terminal.");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "HELP - Lists valid commands to help topic tree.");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "SET_CUST_RGB_CLR,red,green,blue - Custom colour for RGB LED. (arg values 0-256).");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "SET_STD_RGB_CLR,colour - Standard colour for RGB LED. (arg values 0-8).");
         delay(1);
      } //while        
      x = false;
      while(x == false)
      {
         x = mqtt.publishMQTT(helpTopicTree, "ROTATE_OLED,orientation - Orient text on OLED. (arg values 0-3).");
         delay(1);
      } //while        
      Log.noticeln("<processCmd> List of valid MQTT commands sent to MQTT broker."); 
      return true;
   }  // if 
   // SET_CUST_RGB_CLR command.
   if(cmd == "SET_CUST_RGB_CLR")
   {
      const int8_t numArgumentsRequired = 3; // How many arguments expected?
      if(checkNumArg(numArgumentsRequired, argN, &arg[0]))
      {
         uint32_t red = convertStrToUint32_t(arg[1]);
         uint32_t green = convertStrToUint32_t(arg[2]); 
         uint32_t blue = convertStrToUint32_t(arg[3]);
         Log.noticeln("<processCmd> Set RGB LED values R = %u, G = %u, B = %u.", red, green, blue); 
         setCustRgbColour(red, green, blue);
         return true;
      } // if
      else
      {
         return false;
      } // else            
   }  // if 
   // SET_STD_RGB_CLR command.
   if(cmd == "SET_STD_RGB_CLR")
   {   
      const int8_t numArgumentsRequired = 1; // How many arguments expected?
      if(checkNumArg(numArgumentsRequired, argN, &arg[0]))
      {
         uint8_t colour = convertStrToUint8_t(arg[1]);
         setStdRgbColour(colour);
         return true;
      } // if
      else
      {
         return false;
      } // else       
   } // if
   // ROTATE_OLED command.
   if(cmd == "ROTATE_OLED")
   {   
      const int8_t numArgumentsRequired = 1; // How many arguments expected?
      if(checkNumArg(numArgumentsRequired, argN, &arg[0]))
      {
         int8_t tmp = convertStrToInt8_t(arg[1]);
         rotateDisplay(tmp);
         displaySplashScreen("");
         return true;
      } // if
      else
      {
         return false;
      } // else       
   } // if
   Log.warningln("<processCmd> Warning - unrecognized command."); 
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
      Log.noticeln("<checkMqtt> cmd = %s.", cmd.c_str());
      bool allIsWell = processCmd(cmd);
      if(allIsWell)
      {
         Log.noticeln("<checkMqtt> All went well.");
      } // if 
      else
      {
         Log.warningln("<checkMqtt> Something went wrong.");
      } // if 
   } // if   
} // checkMqtt()

#endif // End of precompiler protected code block