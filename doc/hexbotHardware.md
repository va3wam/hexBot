# Hexbot Hardware

Hexbot has a custom chassis designed in Fusion360 and milled out of 6061 extruded aluminium. The robot's has a main body section and six legs. Hexbot's physical properties are:

* Height = ~ 5 inches when in neutral standing position.
* Length = ~ 14 inches when in neutral standing position.
* Weight = ~ 3 lbs 7.5 Oz without battery or PCB.

## Motors

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/mg996r-towerpro-servo-motor.jpg" alt="servo motor" width="100" height="100">
          <figcaption>Fig.1 - Servo motor</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       Hexbot's leg joints are 
       <a href="https://components101.com/motors/mg996r-servo-motor-datasheet">MG996R Servo motors</a>. 
    </td>   
  </tr>
</table>  

## Servo Horns

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/servo-horn.jpg" alt="servo horn" width="100" height="100">
          <figcaption>Fig.2 - Servo horn</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       Each servo motor requires an 
       <a href="https://www.amazon.ca/gp/product/B00NOGMK3M/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1">aluminium round servo horn with a 25 tooth spline</a>. 
    </td>   
  </tr>
</table>  

## Motor Drivers

The Hexpod robot requires a way to connect a large number of servo motors to a microcontroller with limit IO pins. To achieve this we use a pair of Adafruit [PCA9685 16-channel 12-bit servo motor drivers](https://cdn-learn.adafruit.com/downloads/pdf/16-channel-pwm-servo-driver.pdf). These motor drivers have their own onboard NXP Semiconductors [PCA9685 microcontroller](http://www.adafruit.com/datasheets/PCA9685.pdf) that handles the details of PWM signalling to the motors so all we have to do is communicate to them via I2C which only consumes 2 IO pins. The defult I2C address for the driver is 64 (0x40). There is also an all-call address at 112 (0x70). Since hexBot has 18 motors and a single driver can only handle a maximum of 16 we need to use 2 of these drivers. Since both drivers are on the same I2C bus we need to change the I2C address of the second driver to avoid conflicts. Page 13 of the Adafruit document explains how to do this.  

## Line level converter

Since the ESP32 microprocessor used for Hexbot's brain is a 3.3VDC device and the PCA9685 microprocessor used in the motor driver board is a 5 VDC device we must use a line level converter on the I2C bus to connect between them. Hexbot uses the KeeYees [4 Channel I2C Logic Level Converter Bi-Directional Module](https://www.amazon.ca/gp/product/B07LG646VS/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1). 

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

## Assembly
Full step by step instructions for Hexbot can be found [here](hexbotAssembly.md).
