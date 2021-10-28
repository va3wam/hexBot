/*******************************************************************************
 
 # Table of Adafruit Huzzah32 development board pin assignments.
 
 This table details the 21 usable pins on the ESP32-Wrover module that are 
 accessible to us via the Adafrut Huzzah32 development board. The pins are 
 mapped using the silkscreen label on the development board to show which GPIO 
 pins on the Espressif ESP32 Wrover module can be used in an application. Brief 
 notes on each pin are provided in the following table. 
 
 | Board |       |                                                             |
 | Label | Type  | Function                                                    |
 |:-----:|:-----:|:------------------------------------------------------------|
 |: TX  :|: O   :|: Serial1. Not connected to the USB/Serial converter. Used to connect to UART-devices |
 |: RX  :|: I   :|: Serial1. Not connected to the USB/Serial converter. Used to connect to UART-devices |
 |: SCL :|: I/O :|: I2C bus clock. Does not have pullup resistor |
 |: SDA :|: I/O :|: I2C bus data. Does not have pullup resistor |
 |: SCK :|: O   :|: SPI bus clock |
 |: MO  :|: O   :|: SPI bus master out |
 |: MI  :|: I   :|: SPI bus master in |
 |: A0  :|: I/O :|: Analog input A0 and also an analog output DAC2. It can also be used as a GPIO #26. It uses ADC #2 |
 |: A1  :|: I/O :|: Analog input A1 and also an analog output DAC1. It can also be used as a GPIO #25. It uses ADC #2 |
 |: A2  :|: I   :|: Analog input A2 and also GPI #34. Note it is not an output-capable pin! It uses ADC #1 |
 |: A3  :|: I   :|: Analog input A3 and also GPI #39. Note it is not an output-capable pin! It uses ADC #1 |
 |: A4  :|: I   :|: Analog input A4 and also GPI #36. Note it is not an output-capable pin! It uses ADC #1 |
 |: A5  :|: I/O :|: Analog input A5 and also GPIO #4. It uses ADC #2 |
 |: 21  :|: I/O :|: General purpose IO pin #21 |
 |: 13  :|: I/O :|: Analog input A12 on ADC #2 and also GPIO #13. Also connected to the red LED next to the USB port |
 |: 12  :|: O   :|: Analog input A11 on ADC #2 and also GPIO #12. This pin has a pull-down resistor built into it. | 
 |:     :|:     :|: Recommend using as an output only, or making sure that the pull-down is not affected during boot. | 
 |: 27  :|: I/O :|: Analog input A10 on ADC #2 and also GPIO #27. | 
 |: 33  :|: I/O :|: Analog input A9 on ADC #1 and also GPIO #33. It can also be used to connect a 32 KHz crystal | 
 |: 15  :|: I/O :|: Analog input A8 on ADC #2 and also GPIO #15. | 
 |: 32  :|: I/O :|: Analog input A7 on ADC #1 and also GPIO #32. It can also be used to connect a 32 KHz crystal | 
 |: 14  :|: I/O :|: Analog input A6 on ADC #2 and also GPIO #14. | 
 
 Note that you can only read analog inputs on ADC #1 once WiFi has started.
 *******************************************************************************/
#ifndef _HUZZAH32_GPIO_PINS_H // Start of conditional preprocessor code that only allows this library to be included once

#define _HUZZAH32_GPIO_PINS_H // Preprocessor variable used by above check

#include <Arduino.h> // Required for variable type declarations. Arduino Core for ESP32. Comes with Platform.io

/** 
 * The Adafruit Huzzah32 dev board has 28 pins of which 21 are usable to us. 
 * In order for the numbering system used in this file to make sense orient the 
 * board so that the component side is facing up and the USB connector is
 * pointed away from you. This results in the 16 pin header being on the left 
 * and the 12 pin header on the right. Start counting physical pins from the 
 * upper left corner. This is pin 1.
 * 
 * The variable names work as follows: 
 * PIN_<physical pin number>_<silk screen label>.
 * The variable values are the GPIO numbers used in code to reference pins.
 * Physical pins 1 through 4 are not used by our code, nor are physical pins
 * 26 through 28 (see pin comments below for details).
 ******************************************************************************/

///////////////////////////////////////////////////////////////////////////////
// Variables used to reference the pins in the left 16 pin socket.
///////////////////////////////////////////////////////////////////////////////
// Physical pin 1 is labeled RST button
// Physical pin 2 is labeled 3V
// Physical pin 3 is labeled NC
// Physical pin 4 is labeled GND
const int8_t PIN_5_LBL_A0 = 26; // Physical pin 5. Input and output.
const int8_t PIN_6_LBL_A1 = 25; // Physical pin 6. Input and output.
const int8_t PIN_7_LBL_A2 = 34; // Physical pin 7. Input only.
const int8_t PIN_8_LBL_A3 = 39; // Physical pin 8. Input only.
const int8_t PIN_9_LBL_A4 = 36; // Physical pin 9. Input only.
const int8_t PIN_10_LBL_A5 = 4; // Physical pin 10. Input and output.
const int8_t PIN_11_LBL_SCK = 5; // Physical pin 11. Output only.
const int8_t PIN_12_LBL_MO = 18; // Physical pin 12. Output only.
const int8_t PIN_13_LBL_MI = 19; // Physical pin 13. Input only.
const int8_t PIN_14_LBL_RX = 16; // Physical pin 14. Input only.
const int8_t PIN_15_LBL_TX = 17; // Physical pin 15. Output only.
const int8_t PIN_16_LBL_21 = 21; // Physical pin 16. Input and output.
///////////////////////////////////////////////////////////////////////////////
// Variables used to reference the pins in the right 12 pin socket.
///////////////////////////////////////////////////////////////////////////////
const int8_t PIN_17_LBL_SDA = 23; // Physical pin 17. Input and output. 
const int8_t PIN_18_LBL_SCL = 22; // Physical pin 18. Input and output.
const int8_t PIN_19_LBL_14 = 14; // Physical pin 19. Input and output.
const int8_t PIN_20_LBL_32 = 32; // Physical pin 20. Input and output.
const int8_t PIN_21_LBL_15 = 15; // Physical pin 21. Input and output.
const int8_t PIN_22_LBL_33 = 33; // Physical pin 22. Input and output.
const int8_t PIN_23_LBL_27 = 27; // Physical pin 23. Input and output.
const int8_t PIN_24_LBL_12 = 12; // Physical pin 24. Output only.
const int8_t PIN_25_LBL_13 = 13; // Physical pin 25. Input and output.
// Physical pin 26 is labeled USB
// Physical pin 27 is labeled EN
// Physical pin 28 is labeled BAT

#endif // End of conditional preprocessor code