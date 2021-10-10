#ifndef startWebServer_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define startWebServer_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.
bool isWebServer; // True is web server running.
const char* WEB_APP_TITLE = "Hexbot"; // App name for web page titles.
aaWebService localWebService(WEB_APP_TITLE); // Webserver hosted by microcontroller.

/** 
 * @brief Start up the web server.
 * @details Web server supports configuring the MQTT broker IP without needing to 
 *          rebuild. It also provides a web interface for doing OTA code downloads.
 * =================================================================================*/
void startWebServer()
{
   char uniqueName[HOST_NAME_SIZE]; // Contain unique name for Wifi network purposes. 
   char *uniqueNamePtr = &uniqueName[0]; // Pointer to starting address of name. 
   network.getUniqueName(uniqueNamePtr); // Get unique name. 
   Log.noticeln("<startWebServer> Unique Name: %s (Length of %d).", uniqueName, strlen(uniqueName));
   isWebServer = localWebService.start(uniqueNamePtr); // Start web server and track result.
   if(isWebServer)
   {
      Log.noticeln("<startWebServer> Web server successfully started.");
   } //if
   else
   {
      Log.errorln("<startWebServer> Web server failed to start.");
   } //else
} //startWebServer()

#endif // End of precompiler protected code block