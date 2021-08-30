/*************************************************************************************************************************************
 # Table of Adafruit Huzzah32 development board pin assignments.
 This table details the 21 pins on the ESP32-Wrover module that are accessible to us via the Adafrut Huzzah32 development board. The
 pins are mapped using the silkscreen label on the development board to show which GPIO pins on the Espressif ESP32 Wrover module
 can be used in an application. Brief notes on each pin are also shown. 
 
 | Board | GPIO |       |                                                                                                     |
 | Label | Name | Type  | Function                                                                                            |
 |:-----:|:-----:|:-----:|:----------------------------------------------------------------------------------------------------|
 |: TX  :|: 17  :|: O   :|: Serial1 output pin not connected to the USB/Serial converter. Used to connect to UART-devices |
 |: RX  :|: 16  :|: I   :|: Serial1 input pin not connected to the USB/Serial converter. Used to connect to UART-devices |
 |: SCL :|: 22  :|: I/O :|: I2C bus clock. Does not have pullup resistor |
 |: SDA :|: 23  :|: I/O :|: I2C bus data. Does not have pullup resistor |
 |: SCK :|:  5  :|: O   :|: SPI bus clock |
 |: MO  :|: 18  :|: O   :|: SPI bus master out |
 |: MI  :|: 19  :|: I   :|: SPI bus master in |
 |: A0  :|: 26  :|: I/O :|: Analog input A0 and also an analog output DAC2. It can also be used as a GPIO #26. It uses ADC #2 |
 |: A1  :|: 25  :|: I/O :|: Analog input A1 and also an analog output DAC1. It can also be used as a GPIO #25. It uses ADC #2 |
 |: A2  :|: 34  :|: I   :|: Analog input A2 and also GPI #34. Note it is not an output-capable pin! It uses ADC #1 |
 |: A3  :|: 39  :|: I   :|: Analog input A3 and also GPI #39. Note it is not an output-capable pin! It uses ADC #1 |
 |: A4  :|: 36  :|: I   :|: Analog input A4 and also GPI #36. Note it is not an output-capable pin! It uses ADC #1 |
 |: A5  :|:  4  :|: I/O :|: Analog input A5 and also GPIO #4. It uses ADC #2 |
 |: 21  :|: 21  :|: I/O :|: General purpose IO pin #21 |
 |: 13  :|: 13  :|: I/O :|: Analog input A12 on ADC #2 and also GPIO #13. Also connected to the red LED next to the USB port |
 |: 12  :|: 12  :|: O   :|: Analog input A11 on ADC #2 and also GPIO #12. This pin has a pull-down resistor built into it. | 
 |:     :|:     :|:     :|: Recommend using as an output only, or making sure that the pull-down is not affected during boot. | 
 |: 27  :|: 27  :|: I/O :|: Analog input A10 on ADC #2 and also GPIO #27. | 
 |: 33  :|: 33  :|: I/O :|: Analog input A9 on ADC #1 and also GPIO #33. It can also be used to connect a 32 KHz crystal | 
 |: 15  :|: 15  :|: I/O :|: Analog input A8 on ADC #2 and also GPIO #15. | 
 |: 32  :|: 32  :|: I/O :|: Analog input A7 on ADC #1 and also GPIO #32. It can also be used to connect a 32 KHz crystal | 
 |: 14  :|: 14  :|: I/O :|: Analog input A6 on ADC #2 and also GPIO #14. | 
 Note you can only read analog inputs on ADC #1 once WiFi has started
 Also that the physical pin count starts at the reset button on long pin side of the Huzzah32 development board
 *************************************************************************************************************************************/
#ifndef _HUZZAH32_GPIO_PINS_H // Start of conditional preprocessor code that only allows this library to be included once

#define _HUZZAH32_GPIO_PINS_H // Preprocessor variable used by above check

#include <Arduino.h> // Required for variable type declarations. Arduino Core for ESP32. Comes with Platform.io

const int8_t PIN_LBL_TX = 17; // Physical pin 15
const int8_t PIN_LBL_RX = 16; // Physical pin 14
const int8_t PIN_LBL_SCL = 22; // Physical pin 18
const int8_t PIN_LBL_SDA = 23; // Physical pin 17 
const int8_t PIN_LBL_SCK = 5; // Physical pin 11
const int8_t PIN_LBL_MO = 18; // Physical pin 12
const int8_t PIN_LBL_MI = 19; // Physical pin 13
const int8_t PIN_LBL_A0 = 26; // Physical pin 5
const int8_t PIN_LBL_A1 = 25; // Physical pin 6
const int8_t PIN_LBL_A2 = 34; // Physical pin 7
const int8_t PIN_LBL_A3 = 39; // Physical pin 8
const int8_t PIN_LBL_A4 = 36; // Physical pin 9
const int8_t PIN_LBL_A5 = 4; // Physical pin 10
const int8_t PIN_LBL_21 = 21; // Physical pin 16
const int8_t PIN_LBL_13 = 13; // Physical pin 25
const int8_t PIN_LBL_12 = 12; // Physical pin 24
const int8_t PIN_LBL_27 = 27; // Physical pin 23
const int8_t PIN_LBL_33 = 33; // Physical pin 22
const int8_t PIN_LBL_15 = 15; // Physical pin 21
const int8_t PIN_LBL_32 = 32; // Physical pin 20
const int8_t PIN_LBL_14 = 14; // Physical pin 19

#endif // End of conditional preprocessor code