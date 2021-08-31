/*!
 * @file aaNetwork.h  
 * @defgroup globalVariables Class global variables.
 ===================================================================================*/
#ifndef aaNetwork_h // Start precompiler code block. 

#define aaNetwork_h // Precompiler macro used to avoid dupicate inclusion of this code.

/************************************************************************************
 * @section aaNetworkIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <WiFi.h> // Required to connect to WiFi network. Comes with Platform.io.
#include <aaFormat.h> // Collection of handy format conversion functions.
#include <known_networks.h> // Defines Access points and passwords that the robot can scan for and connect to.
#include <ESP32Ping.h> // Verify IP addresses. https://github.com/marian-craciunescu/ESP32Ping.

/*! Valid values for wifi signal strength. */
enum signalStrength 
{
    amazing = -30, ///< -30 db or more is the best signal strength.
    veryGood = -67, ///< -67 db or more is a good signal strength.
    okay = -70, ///< -70 db is a workable signal strength.
    notGood = -80, ///< -80 db may start to have connection issues. 
    unusable = -90, ///< -90 db or less will make the connection unsuable.     
}; //enum

/// Max size of unique network name of this device on the network.  
/// @ingroup globalVariables
static const int8_t HOST_NAME_SIZE = 20; 

/************************************************************************************
 * @class Manage wifi connection to Access Point.
 ************************************************************************************/
class aaNetwork 
{
   public:
      aaNetwork(); // Default class constructor.
      aaNetwork(const char* prefix); // Second form of class constructor.
      ~aaNetwork(); // Class destructor.
      void getUniqueName(char *ptrNameArray); // Construct a name that is sure to be unique on the network.
      bool areWeConnected(); // Return flag reporting if we are wifi connected or not.
      void cfgToConsole(); // Send wifi connection details to console.
      void connect(); // Connect to Wifi.
      long rfSignalStrength(int8_t points); // Collect an average WiFi signal strength. 
      const char* evalSignal(int16_t signalStrength); // Return human readable assessment of signal strength.
      bool pingIP(IPAddress address); // Ping IP address and return response. Assume 1 ping.
      bool pingIP(IPAddress address, int8_t numPings); // Ping IP address and return response. User specified num pings.
   private:
      const char* _lookForAP(); // Scan 2.4GHz radio spectrum for known Access Point.
      const char* _translateEncryptionType(wifi_auth_mode_t encryptionType); // Provide human readable wifi encryption method.
      const char* _connectionStatus(wl_status_t status); // Provide human readable text for wifi connection status codes. 
      static void _wiFiEvent(WiFiEvent_t event, WiFiEventInfo_t info); // Event handler for wifi.
      const char* _unknownAP = "unknown"; // Comparitor used to check if a valid AP was found.
      const char* _ssid; // SSID of Access Point selected to connect to over Wifi. 
      const char* _password; // Password of Access Point selected to connect to over Wifi.
      aaFormat _convert; // Accept various variable type/formats and return a different variable type/format.
      int8_t _SSIDIndex = 0; // Contains the SSID index number from the known list of APs.
      char _uniqueName[HOST_NAME_SIZE]; // Character array that holds unique name for Wifi network purposes. 
      char *_uniqueNamePtr = &_uniqueName[0]; // Pointer to first address position of unique name character array.
      const char* _HOST_NAME_PREFIX; // Prefix for unique network name. 
}; //class aaNetwork

extern aaNetwork wifi; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block