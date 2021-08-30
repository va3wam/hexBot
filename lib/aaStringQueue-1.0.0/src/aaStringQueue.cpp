/******************************************************************************
 * @file aaStringQueue.cpp
 *
 * @mainpage the Aging Apprentice Arduino FIFO String queue class 
 * 
 * @section intro_sec Introduction
 *
 * This is an Arduino class that provides a queue for char[]. It is part of a 
 * series of classes made to support a standard set of APIs for robot platforms. 
 *
 * @section dependencies Dependencies
 * 
 * This class depends on on <a href="https://github.com/espressif/arduino-esp32">
 * Arduino.h</a> being present on your system. This is the Arduino core library
 * that comes bundled with PlatformIO.
 *
 * @section author Author(s)
 *
 * Written by Old Squire for the Aging Apprentice.
 *
 * @section license license
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
 *****************************************************************************/
#include <aaStringQueue.h> // Header file for linking.

// Define global variables.
const int8_t BUFFER_MAX_SIZE = 5;
const int8_t COMMAND_MAX_LENGTH = 20;
char mqttCommandBuffer[BUFFER_MAX_SIZE][COMMAND_MAX_LENGTH] = { "", "", "", "", ""}; // Buffer.

/**
 * @class Provide a FIFO queue for Strings.
 * ==========================================================================*/
aaStringQueue::aaStringQueue()
{

} // aaStringQueue::aaStringQueue()

/**
 * @brief Reports if the command queue is empty or not.
 * @return bool true = it is empty, false = there is at least 1 entry in queue.   
 * ==========================================================================*/
bool aaStringQueue::isEmpty()
{
   if(_numCmdsBuffered == 0)
   {
      return true;
   } //if
   else
   {
      return false;
   } //else
} // aaStringQueue::isEmpty()

/**
 * @brief Reports if the command queue is full or not.
 * @return bool true = it is full, false = there is still room in the queue.   
 * ==========================================================================*/
bool aaStringQueue::isFull() 
{
   if(_numCmdsBuffered >= BUFFER_MAX_SIZE)
   {
      return true;
   } //if
   else
   {
      return false;
   } //else
} // aaStringQueue::isFull()

/**
 * @brief Reports the maximum size of the queue.
 * @return int8_t reports value of BUFFER_MAX_SIZE constant.   
 * ==========================================================================*/
int8_t aaStringQueue::getMaxBufferSize() 
{
   return BUFFER_MAX_SIZE;
} // aaStringQueue::getMaxSize()

/**
 * @brief Reports the number of commands currently in the queue.
 * @return int8_t reports value of the _numCmdsBuffered variable.   
 * ==========================================================================*/
int8_t aaStringQueue::getCount() 
{
   return _numCmdsBuffered;
} // aaStringQueue::getCount()

/**
 * @brief Reports the number of commands that were discarded.
 * @details When the command buffer is full the oldest message is discarded 
 * to make room for a newer message. 
 * @return int8_t reports value of the _numCmdsLost variable.   
 * ==========================================================================*/
int8_t aaStringQueue::getLost() 
{
   return _numCmdsLost;
} // aaStringQueue::getCount()

/**
 * @brief Clears the command queue.
 * @details Actually leaves the values in memory but chnages the counter so 
 * all slots are treated as empty.   
 * ==========================================================================*/
void aaStringQueue::flush() // Clear command queue.
{
   for(int i = BUFFER_MAX_SIZE - 1; i >= 0; i--)
   {
      memset(mqttCommandBuffer[i],0,COMMAND_MAX_LENGTH);      
   } // for
   _numCmdsBuffered = 0;
} // aaStringQueue::flush()

/**
 * @brief Shift command buffer rows down.
 * @details Move each row of command buffer down leaving the top row empty.
 * ==========================================================================*/
void aaStringQueue::_shiftBuffer() // Shift content in buffer down one position.
{
   for(int i = BUFFER_MAX_SIZE - 1; i >= 0; i--)
   {
      strcpy((char*)mqttCommandBuffer[i], (const char *)mqttCommandBuffer[i - 1]);      
   } // for
} // aaStringQueue::_shiftBuffer()

/** 
 * @brief Sends the content of the buffer to the console. 
 * =================================================================================*/
void aaStringQueue::dumpBuffer()
{
   Serial.print("<aaStringQueue::dumpBuffer> Buffer size = "); Serial.println(_numCmdsBuffered);
   Serial.print("<aaStringQueue::dumpBuffer> Lost messages = "); Serial.println(_numCmdsLost);
   for(int i = 0; i <= BUFFER_MAX_SIZE - 1; i++)
   {
      Serial.print("<aaStringQueue::dumpBuffer> Row ");
      Serial.print(i);
      Serial.print(" = "); 
      Serial.println(mqttCommandBuffer[i]);
   } // for
} // aaStringQueue::dumpBuffer()

/** 
 * @brief Adds a new command to the top of the queue.
 * @details Shift all previous commands done in the queue and add thhe newest command
 * to the top. If the queue is full then the bottom item (the odest one) gets dropped
 * and is never processed. The variable _numCmdsLost is used as a counter tracks this 
 * loss. 
 * =================================================================================*/
void aaStringQueue::push(char* newItem) // Add content to top of buffer.
{
   _shiftBuffer();
   strcpy((char*)mqttCommandBuffer[0], newItem);
   _numCmdsBuffered++;
   if(_numCmdsBuffered > BUFFER_MAX_SIZE)
   {
      _numCmdsLost++;
      _numCmdsBuffered = BUFFER_MAX_SIZE;
   } //if
} // aaStringQueue::push()

/** 
 * @brief Puts oldest content from the the buffer into the specified char array.
 * @details Return the oldest command in the buffer. The variable _numCmdsBuffered is
 * used to track the number of buffered command left. Note that the buffer index 
 * starts at 0 so we must subtract one from the index pointer to point at the 
 * corresponding slot. This means that subtracting one from the index counter first 
 * both points at the right slot and et the total number of buffered commands 
 * correctly when we are popping one off the stack.  
 * @param char* A pointer to the character array where the buffer command is placed.
 * =================================================================================*/
void aaStringQueue::pop(char* dest)
{
   if(_numCmdsBuffered > 0)
   {
      _numCmdsBuffered --; // Reduce count and aligns index to 0 based index slot.
      strcpy(dest, (const char*)mqttCommandBuffer[_numCmdsBuffered]); // Pass command. 
      memset(mqttCommandBuffer[_numCmdsBuffered], 0, COMMAND_MAX_LENGTH); // Clear slot.
   } // if
} // aaStringQueue::pop()