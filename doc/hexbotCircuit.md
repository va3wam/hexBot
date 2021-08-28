# Hardware

This page details the hardware used for Hexbot.

## PCB

The circuitry for the Hexbot robot is designed in Eagle CAD and the PCB is fabricated using a third party service. 

## Main processor

The processing logic for the robot is provided by an Espressif DevKit development board which features an Espressif ESP32 System On A Chip 
(SOC). This processor is responsible for handling the logic to balance the robot as well as to handle all the real-time communication with 
an operator as required. We have an article that describes the ESP32 SOC in [greater detail](https://va3wam.github.io/soc/technology%20stack/architecture/SOC-Technology-Stack/) if you are keen to know more about it.

## Motion Sensors

```Not sure if we will use this or not```

The robot’s motion tracking is provided by an Invensense MPU6050 inertial measurement unit development board which combine a 3-axis 
microelectromechanical gyroscope and a 3-axis accelerometer on the same silicon die, together with an onboard Digital Motion Processor (DMP), which processes complex 6-axis MotionFusion algorithms. 

## Power Management

The robot is powered by direct current provided by a Dewalt 20V 3AH lithium-ion battery. This voltage is stepped down to a 12 volt bus, a 5 
volt bus and a 3.3 volt bus using a Drok LM2596 multiple output power supply.  

## Buttons

The robot features a [reset and selection button](https://www.adafruit.com/product/3350) as well as a [power button](https://www.adafruit.com/product/4659). These buttons feature embedded software controlled LEDs that allow for the robot to give visual queues as to what it is doing.

## OLED/LCD

```Not sure what display we will use yet```.
