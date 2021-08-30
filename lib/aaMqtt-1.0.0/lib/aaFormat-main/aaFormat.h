/*!
 * @file aaFormat.h  
 ===================================================================================*/
#ifndef aaFormat_h // Start precompiler code block. 

#define aaFormat_h // Precompiler macro used to avoid dupicate inclusion of this code.

/************************************************************************************
 * @section aaFormatIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.

/************************************************************************************
 * @class Read/write to/from flash RAM.
 ************************************************************************************/
class aaFormat // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaFormat(); // Default constructor for this class.
      ~aaFormat(); // Class destructor.
      const char* noColonMAC(String macAddress); // Returns string of MAC address with no colons in it
      String stringToUpper(String strToConvert); // Retruns string converted to all uppercase
      String ipToString(IPAddress ip); // Returns string of IP address
      void ipToByteArray(const char* str, byte* bytes); // Convert char array containing IP address to byte array
      void macToByteArray(const char* str, byte* bytes); // Convert char array containing MAC address to byte array
      void joinTwoConstChar(const char *a, const char *b, char *out); // Concatinate two const char* arrays  to one buffer.
   private: 
      void _parseBytes(const char* str, char sep, byte* bytes, int8_t maxBytes, int8_t base); // Convert char array (ASCII) to byte array
}; //class aaFormat

extern aaFormat convert; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block