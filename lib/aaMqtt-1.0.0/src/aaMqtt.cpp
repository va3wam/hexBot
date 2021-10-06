/******************************************************************************
 * @file aaMqtt.cpp
 *
 * @mainpage the Aging Apprentice flash memory class 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that handles publish and subscription transactions
 * with an MQTT broker. This is part of a series of classes made to support a 
 * standard set of APIs for robot platforms. 
 *
 * @section dependencies Dependencies
 * 
 * This class depends on on <a href="https://github.com/espressif/arduino-esp32">
 * Arduino.h</a> being present on your system. This is the Arduino core library
 * that comes bundled with PlatformIO.
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
#include <aaMqtt.h> // Header file for linking.
#include <aaStringQueue.h> // Required for string buffer to hold incoming commands.

/************************************************************************************
 * @section mqttGlobalVariables Define global variables. Redo like below. 
 ************************************************************************************/
static TimerHandle_t mqttReconnectTimer; // Instantiate OS software timer.
static const char* uniqueName; // Unique name to prefix all topics with.
static IPAddress brokerIP; // IP address of broker.
static uint16_t BROKER_PORT = 1883; // Port used by MQTT broker. 
static AsyncMqttClient mqttClient; // Instantiate MQTT object.
static const char*  cmdTopicMQTT = "NOTHING"; // Full path to incoming command topic from MQTT broker.
static uint8_t MQTT_QOS = 1; // use Quality of Service level 1 or 0? (0 has less overhead).
static bool _mqttConnected;
aaStringQueue cmdQueue; // Instantiate the command queue.

/************************************************************************************
 * @section mqttDefineConstants Define constants. 
 ************************************************************************************/
const char* TOP_OF_TREE = "agingApprentice/"; // Define top of MQTT topic tree.
const char* HEALTH_MQTT_TOPIC = "/health"; // Define MQTT health topic.
const char* CHECKIN_MQTT_TOPIC = "checkin"; // Define MQTT health topic.
 
/**
 * @class Write variables to flash memory.
 ============================================================================*/
aaMqtt::aaMqtt() 
{
   Serial.println("<aaMqtt::aaMqtt> Default constructor running.");
} // aaMqtt::aaMqtt()

/**
 * @brief This is the destructor for this class.
 =============================================================================*/
aaMqtt::~aaMqtt() 
{
   Serial.println("<aaMqtt::aaMqtt> Destructor running.");
} // aaMqtt::aaMqtt()

/**
 * @brief Connect to MQTT broker.
 * @param IPAddress IP address of the MQTT broker. 
 * @param char* Unique name used to prefix all topic trees.
 =============================================================================*/
void aaMqtt::connect(IPAddress address, const char* uName)
{
   _mqttConnected = false;
   brokerIP = address;
   uniqueName = uName; // Prefix for all MQTT topic tree names.
   Serial.print("<aaMqtt::connect> Connecting as ");
   Serial.print(uniqueName);
   Serial.print(" to MQTT broker at IP address ");
   Serial.print(brokerIP);
   Serial.println(" ...");
   mqttClient.onConnect(onMqttConnect); // Define connection event.
   mqttClient.onDisconnect(onMqttDisconnect); // Define disconnect event.
   mqttClient.onSubscribe(onMqttSubscribe); // Define subscribe event.
   mqttClient.onUnsubscribe(onMqttUnsubscribe); // Define unsubscribe event.
   mqttClient.onMessage(onMqttMessage); // Define recieve message event.
   mqttClient.onPublish(onMqttPublish); // Define publish message event.
   mqttClient.setServer(brokerIP, BROKER_PORT); // Set IP and port for broker service.  
   mqttClient.connect(); // Connect to broker.
} // aaMqtt::connect()

/**
 * @brief Event handler for connecting to the broker.
 * @param bool  Check to see if there are messages queued already. 
 =============================================================================*/
void aaMqtt::onMqttConnect(bool sessionPresent)
{
   Serial.print("<aaMqtt::onMqttConnect> Connected to MQTT. Session present = ");
   Serial.println(sessionPresent);
   char buf[30];
   const char* topic = "/commands";
   cmdTopicMQTT = uniqueName;
   Serial.print("<aaMqtt::onMqttConnect> uniqueName = "); Serial.println(cmdTopicMQTT);
   strcpy(buf, uniqueName);
   strcat(buf, topic);   
   cmdTopicMQTT = buf;   
   uint16_t packetIdSub = mqttClient.subscribe(cmdTopicMQTT, MQTT_QOS); // QOS can be 0,1 or 2. controlled by MQTTQos parameter
   Serial.print("<aaMqtt::onMqttConnect> Subscribing to "); Serial.print(cmdTopicMQTT);
   Serial.print(" at a QOS of "); Serial.print(MQTT_QOS);
   Serial.print(" with a packetId of "); Serial.println(packetIdSub);
   _mqttConnected = true; // Flag that a broker connection now exists.
   publishMQTT(CHECKIN_MQTT_TOPIC,uniqueName); // Checkin with unique name.
   Serial.println("<aaMqtt::onMqttConnect> Send checkin message to broker"); 
} // aaMqtt::onMqttConnect()

/**
 * @brief Event handler for disconnecting from the broker.
 * @param AsyncMqttClientDisconnectReason Reason code. 
 =============================================================================*/
void aaMqtt::onMqttDisconnect(AsyncMqttClientDisconnectReason reason)
{
   _mqttConnected = false;
   Serial.println("<onMqttDisconnect> Disconnected from MQTT");
   if(WiFi.isConnected())
   {
      xTimerStart(mqttReconnectTimer, 0); // Activate mqtt timer (which only runs 1 time)
   } //if
} // void aaMqtt::onMqttDisconnect()

/**
 * @brief Event handler for subscribing to a topic on the broker.
 * @param uint16_t PackID that matches the subscription request. 
 * @param uint8_t SUBACK return code
 *
 * # Suback Message
 * To confirm each subscription, the broker sends a SUBACK acknowledgement 
 * message to the client. This message contains the packet 
 * identifier of the original Subscribe message (to clearly identify the 
 * message) and a list of return codes.
 *
 * ## Packet Identifier 
 * The packet identifier is a unique identifier used to identify a message. 
 * It is the same as in the SUBSCRIBE message.
 *
 * ##Return Code 
 * The broker sends one return code for each topic/QoS-pair that it receives in 
 * the SUBSCRIBE message. For example, if the SUBSCRIBE 
 * message has five subscriptions, the SUBACK message contains five return codes. 
 * The return code acknowledges each topic and shows 
 * the QoS level that is granted by the broker. If the broker refuses a 
 * subscription, the SUBACK message conains a failure return code 
 * for that specific topic. For example, if the client has insufficient 
 * permission to subscribe to the topic or the topic is malformed.
 *
 * # Table of SUBACK return codes
 * | Return Code | Return Code Response |  
 * |:-----------:|:---------------------|
 * |  0  |  Success - Maximum QoS 0 |
 * |  1  |  Success - Maximum QoS 1 |
 * |  2  |  Success - Maximum QoS 2 |
 * | 128 |  Failure | 
 * ===========================================================================*/
void aaMqtt::onMqttSubscribe(uint16_t packetId, uint8_t qos)
{
   Serial.print("<aaMqtt::onMqttSubscribe> Subscribe acknowledged by broker.");
   Serial.print(" PacketId = "); Serial.print(packetId);
   Serial.print(" QOS = "); Serial.println(qos);
} // aaMqtt::onMqttSubscribe()

/**
 * @brief Event handler for subscribing to a topic on the broker.
 * @param uint16_t PackID that matches the unsubscribe request. 
 =============================================================================*/
void aaMqtt::onMqttUnsubscribe(uint16_t packetId)
{

} // aaMqtt::onMqttUnsubscribe()

/**
 * @brief Publishes a message to the MQTT server.
 * @param char* Topic to pubished to.
 * @param char* Message to publish. 
 =============================================================================*/
bool aaMqtt::publishMQTT(const char* topic, const char* msg)
{
   char fullTopic[80] = "";
   strcpy(fullTopic,TOP_OF_TREE); // Move vendor name into full topic name.
   strcat(fullTopic,topic); // Append topic into full topic name.

   if(_mqttConnected == true)
   {
      mqttClient.publish(fullTopic, MQTT_QOS, false, msg);
      return true;
   } //if
   else
   {
      return false;
   } //else
} // aaMqtt::publishMQTT()

/**
 * @brief Publishes an event.
 * @param int Event ID.
 * @param int Event severity.
 * @param String Event message.
 =============================================================================*/
void aaMqtt::publishEvent(int evtId, int evtSev, String evtMsg)
{

} // aaMqtt::publishEvent()

/**
 * @brief Event handler for recieving a message from a subscribed topic.
 * @param char* Topic message pertains to.  
 * @param char* Message payload. 
 * @param AsyncMqttClientMessageProperties Message properties. 
 * @param size_t Length of message payload. 
 * @param size_t Message index. 
 * @param size_t Total length of message.
 =============================================================================*/
void aaMqtt::onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total)
{
   Serial.println("<onMqttMessage> Received message.");
   Serial.print("<onMqttMessage>  topic: ");
   Serial.println(topic);
   Serial.print("<onMqttMessage>  qos: ");
   Serial.println(properties.qos);
   Serial.print("<onMqttMessage>  dup: ");
   Serial.println(properties.dup);
   Serial.print("<onMqttMessage>  retain: ");
   Serial.println(properties.retain);
   Serial.print("<onMqttMessage>  len: ");
   Serial.println(len);
   Serial.print("<onMqttMessage>  index: ");
   Serial.println(index);
   Serial.print("<onMqttMessage>  total: ");
   Serial.println(total);
   Serial.print("<onMqttMessage>  payload: ");
   Serial.println(payload);
   String tmp = String(payload).substring(0, len);
   Serial.print("<onMqttMessage> Message to process = ");
   Serial.println(tmp);
   char msg[30]; // Used to hold message converted from const.
   strcpy(msg, tmp.c_str()); // Convert const char* to char*;
   Serial.print("<onMqttMessage> msg = ");
   Serial.println(msg);
   cmdQueue.push(msg); // Push message onto FIFO buffer stack.
   cmdQueue.dumpBuffer();
} // aaMqtt::onMqttMessage()

/**
 * @brief Event handler for the ACK from a published message.
 * @param uint16_t Packet Id of message that was published.
 =============================================================================*/
String aaMqtt::getCmd()
{
   if(cmdQueue.isEmpty())
   {
      return "";
   } // if
   else
   {
      int8_t strSize = cmdQueue.getMaxBufferSize();
      char str[strSize];
      cmdQueue.pop(str);
      Serial.print("<aaMqtt::getCmd> Size of string = ");
      Serial.println(strSize);
      Serial.print("<aaMqtt::getCmd> Command pulled from buffer = ");
      Serial.println(String(str));
      return String(str);
   } // else
} // aaMqtt::getCmd()

/**
 * @brief Event handler for the ACK from a published message.
 * @param uint16_t Packet Id of message that was published.
 =============================================================================*/
void aaMqtt::onMqttPublish(uint16_t packetId)
{

} // aaMqtt::onMqttPublish()