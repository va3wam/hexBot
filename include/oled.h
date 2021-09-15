#ifndef oled_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define oled_h // Precompiler macro used for precompiler check.

#include <Wire.h> // I2C
#include <Adafruit_GFX.h> // OLED graphics
#include <Adafruit_SH110X.h> // OLED text
#include <hexbot_gpio_pins.h> // GPIO pin uses

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
bool buttonA_flag = false;
bool buttonB_flag = false;
bool buttonC_flag = false;

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
 * @brief Display the splash screen.
 * ==========================================================================*/
void displaySplashScreen() 
{
   // Clear the buffer.
   display.clearDisplay();
   display.display();
   display.setRotation(1);
   // Display splash
   display.setTextSize(3);
   display.setTextColor(SH110X_WHITE);
   display.setCursor(10,20);
   display.print("HEXBOT");
   delay(10);
   yield();      
   display.display(); // actually display all of the above
} // displaySplashScreen()

/**
 * @brief Check to see if any of the OLED buttons have been pressed.
 * ==========================================================================*/
void checkOledButtons() 
{
   if(buttonA_flag == true)
   {
      buttonA_flag = false; 
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(25,0);
      display.println("Configuration \n");
      display.print("Robot: ");
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
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SH110X_WHITE);
      display.setCursor(32,0);
      display.println("Blank Menu \n");
      delay(10);
      yield();      
      display.display(); // actually display all of the above   
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
//   Serial.begin(115200);

   Serial.println("<initOled> 128x64 OLED FeatherWing test");
   display.begin(0x3C, true); // Address 0x3C default
   Serial.println("<initOled> OLED begun");

   // Clear the buffer.
//   display.clearDisplay();
//   display.display();

//   display.setRotation(1);
//   Serial.println("<initOled> Button test");

   pinMode(BUTTON_A, INPUT_PULLUP);
   pinMode(BUTTON_B, INPUT_PULLUP);
   pinMode(BUTTON_C, INPUT_PULLUP);

   attachInterrupt(BUTTON_A, ButtonA_ISR, RISING);
   attachInterrupt(BUTTON_B, ButtonB_ISR, RISING);
   attachInterrupt(BUTTON_C, ButtonC_ISR, RISING);

   displaySplashScreen();
} // setup()

#endif // End of precompiler protected code block