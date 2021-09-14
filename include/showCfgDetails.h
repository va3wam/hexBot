#ifndef showCfgDetails_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define showCfgDetails_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.
#include <connectToMqttBroker.h> // MQTT broker functions.
//#include <i2c.h> // Scan I2C buses to see what devices are present.
const char* HOST_NAME_PREFIX = "Hexbot"; // Prefix for our unique network name.
aaChip appCpu; // Access information about the ESP32 application microprocessor (Core1).
aaNetwork network(HOST_NAME_PREFIX); // WiFi session management.
bool networkConnected = false;
bool mqttBrokerConnected = false;
bool oledConnected = false;
bool motorController1Connected = false;
bool motorController2Connected = false;

/** 
 * @brief Show the environment details of this application.
 * =================================================================================*/
void showCfgDetails()
{
   Serial.println("<showCfgDetails> Robot Configuration Report");
   Serial.println("<showCfgDetails> ==========================");
   appCpu.cfgToConsole(); // Display core0 information on the console.
   if(networkConnected == true)
   {
      Serial.println("<showCfgDetails> Network connection status = TRUE");
      network.cfgToConsole(); // Display network information on the console.
      if(mqttBrokerConnected == true)
      {
         Serial.println("<showCfgDetails> MQTT broker connection status = TRUE");
         Serial.print("<showCfgDetails> MQTT broker IP address = ");
         Serial.println(getMqttBrokerIP());
      } // if
      else
      {
         Serial.println("<showCfgDetails> MQTT broker connection status = FALSE");
      } // else
   } // if
   else
   {
      Serial.println("<showCfgDetails> Network connection status = FALSE");
   } // else
   if(oledConnected == true)
   {
      Serial.println("<showCfgDetails> OLED connection status = TRUE.");
   } // if
   else
   {
      Serial.println("<showCfgDetails> OLED connection status = FALSE.");
   } // else
   if(motorController1Connected == true)
   {
      Serial.println("<showCfgDetails> Left servo driver connection status = TRUE.");
   } // if
   else
   {
      Serial.println("<showCfgDetails> Left servo driver connection status = FALSE.");
   } // else
   if(motorController2Connected == true)
   {
      Serial.println("<showCfgDetails> Right servo driver connection status = TRUE.");
   } // if
   else
   {
      Serial.println("<showCfgDetails> Right servo driver connection status = FALSE.");
   } // else
} //showCfgDetails()

#endif // End of precompiler protected code block