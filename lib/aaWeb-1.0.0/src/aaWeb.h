/*!
 * @file aaWeb.h  
 ===================================================================================*/
#ifndef aaWeb_h // Start precompiler code block. 

#define aaWeb_h // Precompiler macro used to avoid dupicate inclusion of this code.

/************************************************************************************
 * @section aaWebIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <Preferences.h> // Saving variables into Flash memory. Comes with Platform.io.
#include <Update.h> // Library used to update firmware. Comes with Platform.io.
#include <WiFiClient.h> // Communicating with web browser. Comes with Platform.io.
#include <WebServer.h> // Hosting an HTTP server on the ESP32. Comes with Platform.io.
#include <ESPmDNS.h> // Redirecting of incoming cient requests. Comes with Platform.io.
#include <ESP32Ping.h> // Verify IP addresses. https://github.com/marian-craciunescu/ESP32Ping

/************************************************************************************
 * @section aaWebServiceVars Global variables.
 ************************************************************************************/
static WebServer server(80); // Declare web server instance usng port 80.
static String _webPageStyle; // Cascading style sheet for web pages.
static String _loginPage; // Login web page.
static String _optionPage; // Option web page.
static String _cfgPage; // Configuration web page.
static String _otaPage; // Over The Air upload Page.

/************************************************************************************
 * @class Read/write to/from flash RAM.
 ************************************************************************************/
class aaWeb // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaWeb(); // Default constructor for this class.
      aaWeb(const char* var1); // Second form of class constructor.
      ~aaWeb(); // Class destructor.
      bool start(char *uniqueNamePtr); // Start web server.
      bool checkForClientRequest(); // Check for web client requests.
      static bool newMqttBrokerIp(const char* address); // Handle new IP address for broker from web.
      IPAddress getBrokerIP(); // Get new broker IP address.
   private:
      void _cfgLoginPageHandler(); // Configure the main web page handler.
      void _cfgOptionPageHandler(); // Configure the option web page handler.
      void _cfgCfgPageHandler(); // Configure the configuration web page handler.
      void _cfgOtaPageHandler(); // Configure the OTA web page handler.
      void _cfgSetMqttPageHandler(); // Configure the set MQTT web page handler.
      void _cfgSelectBinaryPageHandler(); // Configuure the select binary web page handler.
      void _defineStyleSheet(); // Defines style sheet used for all web pages. 
      void _defineLoginPage(const char* nameForTitles); //  Define login web page;
      static void _defineOptionPage(const char* nameForTitles); // Define options web page
      void _defineCfgPage(const char* nameForTitles); // Define configuration web page.
      void _defineOtaPage(const char* nameForTitles); // Define OTA download web page.               
}; //class aaWeb

extern aaWeb myWebServer; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block