/*******************************************************************************
 * @file oled.cpp  
 * @brief File containing all OLED functions.
 *******************************************************************************/
#ifndef oled_cpp // Start of precompiler check to avoid dupicate inclusion of this code block.

#define oled_cpp // Precompiler macro used for precompiler check.

#include <main.h> // Header file for all libraries needed by this program.

/**
 * @brief Hardware Interrupt Service Routine for Button A on OLED display.
 * ==========================================================================*/
void IRAM_ATTR ButtonA_ISR() 
{
   buttonA_flag = true;    
} // ButtonA_ISR()

/**
 * @brief Hardware Interrupt Service Routine for Button B on OLED display.
 * ==========================================================================*/
void IRAM_ATTR ButtonB_ISR() 
{
   buttonB_flag = true;    
} // ButtonB_ISR()

/**
 * @brief Hardware Interrupt Service Routine for Button C on OLED display.
 * ==========================================================================*/
void IRAM_ATTR ButtonC_ISR() 
{
   buttonC_flag = true;    
} // ButtonC_ISR()

/**
 * @brief Places a text message centrered vertically and horizontally.
 * 
 * @param msg A text message to be displayed.
 * @param fontSize Multiplier of base text size (6px X 8px). Usually 1-3.
 * @param fontColour SH110X_WHITE is the usual choice here.
 * ==========================================================================*/
void placeTextVHcentre(String msg, uint8_t fontSize, uint16_t fontColour) 
{
   display.setTextSize(fontSize);
   display.setTextColor(fontColour);
   uint8_t x = (oledX - (textBaseX * fontSize * msg.length())) / 2; 
   uint8_t y = (oledY - (textBaseY * fontSize)) / 2;  
   display.setCursor(x, y);
   display.print(msg);
} // placeTextVHcentre

/**
 * @brief Places a text message centrered horizontally.
 * 
 * @param msg A text message to be displayed.
 * @param fontSize Multiplier of base text size (6px X 8px). Usually 1-3.
 * @param fontColour SH110X_WHITE is the usual choice here.
 * ==========================================================================*/
void placeTextHcentre(String msg, uint8_t fontSize, uint16_t fontColour) 
{
   display.setTextSize(fontSize);
   display.setTextColor(fontColour);
   uint8_t x = (oledX - (textBaseX * fontSize * msg.length())) / 2; 
   display.setCursor(x, display.getCursorY());
   display.println(msg);
} // placeTextHcentre()

/**
 * @brief Rotate the display.
 * @details Does not rotate the current screen content but will affect all
 * new content sent t the OLED. Note that the the setRotation() function 
 * orients the content displayed on the OLED screen using a 1 byte parameter 
 * which has does the following:
 * 0 sets the orietation so that the top is where the buttons are.  
 * 1 rotates the top of the display 90 degrees clockwise from position 0. 
 * 2 rotates the top of the display 180 degrees clockwise from position 0. 
 * 3 rotates the top of the display 270 degrees clockwise from position 0. 
 * @param newOrientation which of the 4 valid orientations to use.
 * ==========================================================================*/
void rotateDisplay(int8_t newOrientation) 
{
   switch(newOrientation)
   {
      case 0:
         Log.verboseln("<rotateDisplay> OLED top is now where the buttons are.");
         oledOrientation = newOrientation;
         display.setRotation(oledOrientation); // Orient screen content. 
         break;
      case 1:
         Log.verboseln("<rotateDisplay> OLED top is now 90 degrees clockwise from where the buttons are.");
         oledOrientation = newOrientation;
         display.setRotation(oledOrientation); // Orient screen content. 
         break;
      case 2:
         Log.verboseln("<rotateDisplay> OLED top is now 180 degrees clockwise from where the buttons are.");
         oledOrientation = newOrientation;
         display.setRotation(oledOrientation); // Orient screen content. 
         break;
      case 3:
         Log.verboseln("<rotateDisplay> OLED top is now 270 degrees clockwise from where the buttons are.");
         oledOrientation = newOrientation;
         display.setRotation(oledOrientation); // Orient screen content. 
         break;
      default:
         Log.errorln("<rotateDisplay> Invalid OLED orientation request of %d. Only values 0-3 are allowed.", newOrientation);
         break;
   } // switch
} // rotateDisplay()

/**
 * @brief Display the splash screen.
 * @details Clear the OLED display, set the orientation then display the 
 * splash screen. Note that the the setRotation() function orients the content
 * displayed on the OLED screen using a 1 byte parameter which has does the 
 * following:
 * 0 sets the orietation so that the top is where the buttons are.  
 * 1 rotates the top of the display 90 degrees clockwise from position 0. 
 * 2 rotates the top of the display 180 degrees clockwise from position 0. 
 * 3 rotates the top of the display 270 degrees clockwise from position 0. 
 * @param msg Text message to add as tag line to splash screen.
 * ==========================================================================*/
void displaySplashScreen(String msg) 
{
   if(oledConnected == false)
   {
      Log.warningln("<displaySplashScreen> OLED missing. Message suppressed.");
      return;
   } // if
   int8_t headingSize = 3;
   int8_t subMsgSize = 1;
   display.clearDisplay(); // Clear the buffer.
   if(msg == "") // No sub heading message
   {
      placeTextVHcentre("HEXBOT", headingSize, SH110X_WHITE); 
   } // if
   else
   {
      placeTextVHcentre("HEXBOT", headingSize, SH110X_WHITE); 
      placeTextHcentre(msg, subMsgSize, SH110X_WHITE); 
   } // else
   delay(10); // Wait for buffer.
   yield(); // Periodic yield call to avoid watchdog reset.     
   display.display(); // Actually display all of the above
} // displaySplashScreen()

/**
 * @brief Display what the legs are doing.
 * ==========================================================================*/
void displayStatusScreen() 
{
   if(oledConnected == false)
   {
      Log.warningln("<displayStatusScreen> OLED missing. Message suppressed.");
      return;
   } // if
   display.clearDisplay();
   display.setCursor(0, 0);
   placeTextHcentre("Robot Status", 1, SH110X_WHITE);
   display.print("\nWifi: ");
   // Wifi status.
   if(networkConnected == true)
   {
      display.println("OK");
   } // if
   else
   {
      display.println("ERR");
   } // else
   // MQTT broker connection status.
   display.print("MQTT: ");
   if(mqttBrokerConnected == true)
   {
      display.println("OK");
   } // if
   else
   {
      display.println("ERR");
   } // else
   // Mobility status (if leg servo controllers are detected on I2C).
   display.print("Legs: ");
   if(mobilityStatus == true)
   {
      display.println("OK");
   } // if
   else
   {
      display.println("ERR");
   } // else
   // Current robot goal.
   display.print("Goal: ");
   display.println(legDirExpl[legDirIndex]);
   delay(10);
   yield();      
   display.display(); // actually display all of the above   
} // displayStatusScreen()

/**
 * @brief Check to see if any of the OLED buttons have been pressed.
 * ==========================================================================*/
void checkOledButtons() 
{
   if(buttonA_flag == true)
   {
      buttonA_flag = false; 
      display.clearDisplay();
      display.setCursor(0, 0);
      placeTextHcentre("Configuration", 1, SH110X_WHITE);
      display.print("\nRobot: ");
      display.println(WiFi.localIP());
      display.print("Broker: ");
      display.println(getMqttBrokerIP());
      delay(10);
      yield();      
      display.display(); // actually display all of the above   
   } // if
   if(buttonB_flag == true)
   {
      buttonB_flag = false; 
      displayStatusScreen();
   } // if
   if(buttonC_flag == true)
   {
      buttonC_flag = false; 
      displaySplashScreen("");
   } // if
} // loop()

/**
 * @brief Initiaize OLED display.
 * ==========================================================================*/
void initOled() 
{
   if(oledConnected == false)
   {
      Log.warningln("<initOled> OLED missing. Skipping initialization.");
      return;
   } // if
   Log.verboseln("<initOled> 128x64 OLED FeatherWing setup.");
   display.begin(0x3C, true); // Address 0x3C default
   Log.verboseln("<initOled> OLED begun.");
   pinMode(G_BUTTON_A, INPUT_PULLUP); // Make button A pin input with weak pullup.
   pinMode(G_BUTTON_B, INPUT_PULLUP); // Make button B pin input with weak pullup.
   pinMode(G_BUTTON_C, INPUT_PULLUP); // Make button C pin input with weak pullup.
   attachInterrupt(G_BUTTON_A, ButtonA_ISR, RISING); // Assign ISR for button A.
   attachInterrupt(G_BUTTON_B, ButtonB_ISR, RISING); // Assign ISR for button B.
   attachInterrupt(G_BUTTON_C, ButtonC_ISR, RISING); // Assign ISR for button C.
   rotateDisplay(oledOrientation); // Orient OLED text.
   displaySplashScreen("");
} // setup()

#endif // End of precompiler protected code block