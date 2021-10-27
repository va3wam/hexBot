/*******************************************************************************
 * @file terminal.cpp  
 * @brief File containing all terminal functions.
 *******************************************************************************/
#ifndef terminal_cpp // Start of precompiler check to avoid dupicate inclusion of this code block.

#define terminal_cpp // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

/**
 * @brief Initialize the serial output.
 * ==========================================================================*/
void setupSerial()
{
   Serial.begin(serialBaudRate); // Open a serial at specified baud rate. 
   while(!Serial); // Wait for Serial port to be ready.
} //setupSerial()

#endif // End of precompiler protected code block