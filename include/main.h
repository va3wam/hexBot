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
#include <known_networks.h> // String arrays of known Access Points and their passwords.
#include <InverseK.h> // https://github.com/cgxeiji/CGx-InverseK.
#include <Wire.h> // Required for I2C communication.
#include <Adafruit_PWMServoDriver.h> // https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library.
#include <ArduinoLog.h> // https://github.com/thijse/Arduino-Log.
#include <Adafruit_GFX.h> // OLED graphics
#include <Adafruit_SH110X.h> // OLED text
#include <hexbot_gpio_pins.h> // GPIO pin uses

/************************************************************************************
 * @section funDeclare Declare functions found in the include files.
 * @details In order to get rid of "error: 'xxx' was not declared in this scope"
 * compiler errors list a function from any of the include filles here. 
 ************************************************************************************/
void rotateDisplay(int8_t); 
void displaySplashScreen(String);

/*******************************************************************************
 * @section codeModules Functions put into files according to function.
 * @details Order functions here in a way that ensures that variables get 
 * declared in one function prior to being referenced by another function. 
 *******************************************************************************/
#include <huzzah32_gpio_pins.h> // Map pins on Adafruit Huzzah32 dev board to friendly names.
#include <hexbot_gpio_pins.h> // Map Hexbot specific pin naming to generic development board pin names. 
#include <terminal.h> // Serial port management.
#include <configDetails.h> // Show the environment details of this application.
#include <web.h> // Manage locally hosted web service. 
#include <rgbLed.h> // Control status LEDs.
#include <network.h> // Control networking activities.
#include <mqttBroker.h> // Establish connect to the the MQTT broker.
#include <i2c.h> // Scan I2C buses to see what devices are present.
#include <ikLibrary.h> // InverseK.h inverted kinematic functions.
#include <servoLegs.h> // Control leg servos.
#include <oled.h> // Control OLED.
#include <daeIK.h> // Doug's inverted kinetics functions. 

/************************************************************************************
 * @section mainDeclare Declare functions in main.cpp.
 ************************************************************************************/

void setup(); // Arduino mandatory function #1. Runs once at boot. 
void loop(); // Arduino mandatory function #2. Runs continually.

#endif // End of precompiler protected code block