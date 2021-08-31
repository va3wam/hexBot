/*******************************************************************************
 * @file main.h  
 *******************************************************************************/
#ifndef main_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define main_h // Precompiler macro used for precompiler check.

/*******************************************************************************
 * @section mainIncludes Included libraries.
 *******************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with PlatformIO.
#include <aaChip.h> // Core (CPU) details that the code running on.
#include <aaNetwork.h> // Wifi functions. 
#include <aaWebService.h> // Realtime web-based network config and OTA code updates.
#include <aaFlash.h> // Use Flash memory to store values that persist past reboot.
#include <aaMqtt.h> // Use MQTT for remote management and monitoring.
#include <huzzah32_gpio_pins.h> // Map pins on Adafruit Huzzah32 dev board to friendly names.
#include <hexbot_gpio_pins.h> // Map Hexbot specific pin naming to generic development board pin names. 
#include <known_networks.h> // String arrays of known Access Points and their passwords.

/************************************************************************************
 * @section mainConstants Define constant values. 
 ************************************************************************************/
const char* HOST_NAME_PREFIX = "Hexbot"; // Prefix for our unique network name.
const char* WEB_APP_TITLE = "Hexbot"; // App name for web page titles.
char healthTopicTree[50] = ""; // Char array to hold full health topic tree name.

/************************************************************************************
 * @section mainInstantiate Instantiated objects.
 ************************************************************************************/
aaChip appCpu; // Access information about the ESP32 application microprocessor (Core1).
//aaFormat convert; // Assortment of handy conversion functions.
aaNetwork network(HOST_NAME_PREFIX); // WiFi session management.
aaWebService localWebService(WEB_APP_TITLE); // Webserver hosted by microcontroller.
aaFlash flash; // Non-volatile memory management. 
aaMqtt mqtt; // Publish and subscribe to MQTT broker. 

/************************************************************************************
 * @section mainGlobalVar Declare global variables.
 ************************************************************************************/
bool isWebServer; // True is web server running.
IPAddress brokerIP; // IP address of the MQTT broker.
char uniqueName[HOST_NAME_SIZE]; // Character array that holds unique name for Wifi network purposes. 
char *uniqueNamePtr = &uniqueName[0]; // Pointer to first address position of unique name character array.

/************************************************************************************
 * @section mainDeclare Declare functions.
 ************************************************************************************/
void setupSerial(); // Initialize the serial output.
void showCfgDetails(); // Show the environment details of this application.
void startWebServer(); // Start up the local web server service.
void connectToMqttBroker(); // Establish connect to the the MQTT broker. 
void monitorWebServer(); // Look after pending web server requests.
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.



#endif // End of precompiler protected code block