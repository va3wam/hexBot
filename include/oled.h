#ifndef oled_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define oled_h // Precompiler macro used for precompiler check.

#include <Wire.h> // I2C
#include <Adafruit_GFX.h> // OLED graphics
#include <Adafruit_SH110X.h> // OLED text
#include <hexbot_gpio_pins.h> // GPIO pin uses

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
bool buttonA_flag = false; // Flag used by hardware ISR for button A.
bool buttonB_flag = false; // Flag used by hardware ISR for button B.
bool buttonC_flag = false; // Flag used by hardware ISR for button C.

uint8_t oledX = 128; // Screen width in pixels.
uint8_t oledY = 64; // Screen height in pixels.
uint8_t textBaseX = 6; // Smallest font width in pixels.
uint8_t textBaseY = 8; // Smallest font height in pixels.

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
 * @brief Display the splash screen.
 * ==========================================================================*/
void displaySplashScreen() 
{
   display.clearDisplay(); // Clear the buffer.
   display.display(); // Display cleared buffer.
   display.setRotation(1); // Not sure what this does but its in the example.
   placeTextVHcentre("HEXBOT", 3, SH110X_WHITE); // Place logo on screen.
   delay(10); // Wait for buffer.
   yield(); // Not sure what this does but was in example.     
   display.display(); // Actually display all of the above
} // displaySplashScreen()

/**
 * @brief Display what the legs are doing.
 * ==========================================================================*/
void displayLegScreen() 
{
   display.clearDisplay();
   display.setCursor(0, 0);
   placeTextHcentre("Leg Tracking", 1, SH110X_WHITE);
   display.print("\nStatus: ");
   if(legStatus == true)
   {
      display.println("OK");
   } // if
   else
   {
      display.println("ERR");
   } // else
   display.print("Goal: ");
   display.println(legDirExpl[legDirIndex]);
   delay(10);
   yield();      
   display.display(); // actually display all of the above   
} // displayLegScreen()

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
      displayLegScreen();
   } // if
   if(buttonC_flag == true)
   {
      buttonC_flag = false; 
      displaySplashScreen();
   } // if
} // loop()

/**
 * @brief Initiaize OLED display.
 * ==========================================================================*/
void initOled() 
{
   Log.verboseln("<initOled> 128x64 OLED FeatherWing test");
   display.begin(0x3C, true); // Address 0x3C default
   Log.verboseln("<initOled> OLED begun");
   pinMode(BUTTON_A, INPUT_PULLUP); // Make button A pin input with weak pullup.
   pinMode(BUTTON_B, INPUT_PULLUP); // Make button B pin input with weak pullup.
   pinMode(BUTTON_C, INPUT_PULLUP); // Make button C pin input with weak pullup.
   attachInterrupt(BUTTON_A, ButtonA_ISR, RISING); // Assign ISR for button A.
   attachInterrupt(BUTTON_B, ButtonB_ISR, RISING); // Assign ISR for button B.
   attachInterrupt(BUTTON_C, ButtonC_ISR, RISING); // Assign ISR for button C.
   displaySplashScreen();
} // setup()

#endif // End of precompiler protected code block