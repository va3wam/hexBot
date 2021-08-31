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

/*******************************************************************************
 * @section codeModules Functions put into files according to function.
 * @details Order functions here in a way that ensures that variables get 
 * declared in one function prior to being referenced by another function. 
 *******************************************************************************/
#include <setupSerial.h> // Serial port initialization.
#include <showCfgDetails.h> // Show the environment details of this application.
#include <startWebServer.h> // Start up the web server service. 
#include <connectToMqttBroker.h> // Establish connect to the the MQTT broker.
#include <monitorWebServer.h> // Monitor the web server service.

/************************************************************************************
 * @section mainDeclare Declare functions.
 ************************************************************************************/
void setupSerial(); // Initialize the serial output.
void showCfgDetails(); // Show the environment details of this application.
void startWebServer(); // Start up the local web server service.
void monitorWebServer(); // Look after pending web server requests.
void connectToMqttBroker(); // Establish connect to the the MQTT broker. 
void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block