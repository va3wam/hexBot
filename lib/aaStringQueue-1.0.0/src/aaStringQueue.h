/*!
 * @file aaStringQueue.h
 ============================================================================*/

#ifndef aaStringQueue_h // Start of precompiler code block. Avoid duplicate inclusion.

#define aaStringQueue_h // Precompiler macro used for precompiler check.

#include <Arduino.h> // Arduino Core for ESP32. Comes with Platform.io

// Declare global variablles.
extern const int8_t BUFFER_MAX_SIZE;
extern const int8_t COMMAND_MAX_LENGTH;

class aaStringQueue // Define aaStringQueue class 
{
   public:
      aaStringQueue(); // Class constructor.
      bool isEmpty(); // Check if buffer is empty.
      bool isFull(); // Check if buffer is full.
      int8_t getMaxBufferSize(); // Return max size of command buffer.
      int8_t getCount(); // Return the current count of commands buffered. 
      int8_t getLost(); // Return the number of commands that fell off the buffer. 
      void dumpBuffer(); // Sends the content of the buffer to the console.
      void flush(); // Clear command queue.
      void push(char*); // Add content to top of buffer.
      void pop(char*); // Puts oldest content from the the buffer into the specified char array.
   private:
      void _shiftBuffer(); // Shift content in buffer down one position.
      int8_t _numCmdsLost = 0; // Count messages dropped off the bottom of the buffer. 
      int8_t _numCmdsBuffered = 0; // Count messages currently in the buffer. 
}; //class aaStringQueue

extern aaStringQueue cmdBuffer; // Expose all public variables and methods for libraries.

#endif // End of precompiler protected code block.