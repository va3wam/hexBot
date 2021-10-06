/*!
 * @file aaMqtt.h  
 ===================================================================================*/
#ifndef aaMqtt_h // Start precompiler code block. 

#define aaMqtt_h // Precompiler macro used to avoid dupicate inclusion of this code.

/************************************************************************************
 * @section aaMqttIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io.
#include <AsyncMqttClient.h> // MQTT. https://github.com/marvinroger/async-mqtt-client.
#include "freertos/FreeRTOS.h" // OS threads. Comes with Platform.io.
#include "freertos/timers.h" // Software Timers. Comes with Platform.io.
#include <aaNetwork.h> // Store values that persist past reboot.
#include <aaFlash.h> // Use Flash memory to store values that persist past reboot.

/************************************************************************************
 * @section mqttDeclareConstants Declare constants. 
 ************************************************************************************/
extern const char* TOP_OF_TREE; // Declare top of MQTT topic tree.
extern const char* HEALTH_MQTT_TOPIC; // Declare MQTT health topic.
extern const char* CHECKIN_MQTT_TOPIC; // Declare MQTT health topic.

/************************************************************************************
 * @class Read/write to/from flash RAM.
 ************************************************************************************/
class aaMqtt // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaMqtt(); // Default constructor for this class.
      ~aaMqtt(); // Class destructor.
      static void connect(IPAddress address, const char* uniqueName); // Connect to MQTT broker.
      static void onMqttConnect(bool sessionPresent);
      static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason); 
      static void onMqttSubscribe(uint16_t packetId, uint8_t qos);
      static void onMqttUnsubscribe(uint16_t packetId);
      static bool publishMQTT(const char* topic, const char* msg);
      static void publishEvent(int evtId, int evtSev, String evtMsg);
      static void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);
      static void onMqttPublish(uint16_t packetId);
      static String getCmd(); // Checks if there is a command in the queue returns the command or "" is there is not.
   private: 
}; //class aaMqtt

extern aaMqtt mqttBroker; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block