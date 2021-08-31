#ifndef showCfgDetails_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define showCfgDetails_h // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.
const char* HOST_NAME_PREFIX = "Hexbot"; // Prefix for our unique network name.
aaChip appCpu; // Access information about the ESP32 application microprocessor (Core1).
aaNetwork network(HOST_NAME_PREFIX); // WiFi session management.

/** 
 * @brief Show the environment details of this application.
 * =================================================================================*/
void showCfgDetails()
{
   Serial.println("<showCfgDetails> Robot Configuration Report");
   Serial.println("<showCfgDetails> ==========================");
   appCpu.cfgToConsole(); // Display core0 information on the console.
   network.cfgToConsole(); // Display network information on the console.
} //showCfgDetails()

#endif // End of precompiler protected code block