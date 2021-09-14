#ifndef oled_h // Start of precompiler check to avoid dupicate inclusion of this code block.

#define oled_h // Precompiler macro used for precompiler check.

#include <Wire.h> // I2C
#include <Adafruit_GFX.h> // OLED graphics
#include <Adafruit_SH110X.h> // OLED text

Adafruit_SH1107 display = Adafruit_SH1107(64, 128, &Wire);
#define BUTTON_A 15
#define BUTTON_B 32
#define BUTTON_C 14

void initOled() 
{
   Serial.begin(115200);

   Serial.println("128x64 OLED FeatherWing test");
   display.begin(0x3C, true); // Address 0x3C default
   Serial.println("OLED begun");

   // Show image buffer on the display hardware.
   // Since the buffer is intialized with an Adafruit splashscreen
   // internally, this will display the splashscreen.
//   display.display();
//   delay(1000);

   // Clear the buffer.
   display.clearDisplay();
   display.display();

   display.setRotation(1);
   Serial.println("Button test");

   pinMode(BUTTON_A, INPUT_PULLUP);
   pinMode(BUTTON_B, INPUT_PULLUP);
   pinMode(BUTTON_C, INPUT_PULLUP);

   // text display tests
   display.setTextSize(1);
   display.setTextColor(SH110X_WHITE);
   display.setCursor(0,0);
   display.print("Test");
   display.display(); // actually display all of the above
} // setup()

void checkOledButtons() 
{
   if(!digitalRead(BUTTON_A)) display.print("A");
   if(!digitalRead(BUTTON_B)) display.print("B");
   if(!digitalRead(BUTTON_C)) display.print("C");
   delay(10);
   yield();
   display.display();
} // loop()

#endif // End of precompiler protected code block