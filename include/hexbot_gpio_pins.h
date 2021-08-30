/*************************************************************************************************************************************
 Note that the physical pin count starts at the reset button on long pin side of the Huzzah32 development board.
 *************************************************************************************************************************************/
#ifndef _HEXBOT_GPIO_PINS_H // Start of conditional preprocessor code that only allows this library to be included once

#define _HEXBOT_GPIO_PINS_H // Preprocessor variable used by above check

#include <huzzah32_gpio_pins.h> // Mapping of ESP32 pins to Huzzah32 development board pins

const int8_t I2C_BUS0_SDA = PIN_LBL_SDA; // Serial Data Line (SDA) for I2C bus 0, physical pin 17
const int8_t I2C_BUS0_SCL = PIN_LBL_SCL; // Serial Clock Line (SCL) for I2C bus 0, physical pin 18
const int8_t I2C_BUS1_SDA = PIN_LBL_TX; // Serial Data Line (SDA) for I2C bus 1, physical pin 15
const int8_t I2C_BUS1_SCL = PIN_LBL_21; // Serial Clock Line (SCL) for I2C bus 1, physical pin 16

#endif // End of conditional preprocessor code