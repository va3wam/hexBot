/*!
 * @file aaChip.h
 *
 * This is an Arduino class that retrieves information about the microprocessor
 * that is hosting the Arduino binary. It is part of a series of classes made 
 * to support a standard set of APIs for robot platforms.  
 *
 * Written by Old Squire for the Aging Apprentice.
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
 ============================================================================*/

#ifndef aaChip_h // Start of precompiler code block. Avoid duplicate inclusion.

#define aaChip_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

class aaChip // Define aaChip class 
{
   public:
      aaChip(); // Constructor
      void cfgToConsole();
      const char* getSDKVer();
      const char* getChipModel();
      uint8_t getChipRevision();
      uint32_t getSerialSpeed();
      uint32_t getCodeSize();
      uint32_t getFreeHeap();
      uint32_t getCpuId();
      uint32_t getCpuClock();
   private:
}; //class aaChip

extern aaChip appCore; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block.