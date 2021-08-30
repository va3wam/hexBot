/*!
 * @file aaFlash.h  
 ===================================================================================*/
#ifndef aaFlash_h // Start precompiler code block. 

#define aaFlash_h // Precompiler macro used to avoid dupicate inclusion of this code.

/************************************************************************************
 * @section aaFlashIncludes Included libraries.
 ************************************************************************************/
#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io.
#include <Preferences.h> // Required for saving variables into Flash memory.

/************************************************************************************
 * @class Read/write to/from flash RAM.
 ************************************************************************************/
class aaFlash // Indicate that we are extending LiquidCrystal_I2C class with our class 
{
   public:
      aaFlash(); // Default constructor for this class.
      aaFlash(const char* var1); // Second form of class constructor.
      ~aaFlash(); // Class destructor.
      IPAddress readBrokerIP(); // Read from flash memory.
      void writeBrokerIP(IPAddress address); // Write to flash memory.
   private: 
}; //class aaFlash

extern aaFlash flashMem; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block