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
          <img src="/img/assembledLeftLeg v2.png" alt="Left Leg">
          <figcaption>Fig.1 - Hexbot left leg assembly</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       The three leg joint motors are [MG996R Servo motors](https://components101.com/motors/mg996r-servo-motor-datasheet). Each of the three motors require a [Mallofusa 25 tooth Servo Horn](https://www.amazon.ca/Mallofusa-Servo-Aluminum-Silvery-Helicopter/dp/B00NOGMK3M). Our testing has taught us the following:

* Use a frequency of 50Hz (20ms period) for the PWM signal used to control these motors.
* A 50% duty cycle puts the motor in it's centre position. 
* The practical movement range of these motors is 60 degrees to either side of centre so rather than using the lower movement limit of 0 degrees use 30 degrees. Rather than using the upper movement limit of 128 use 150 degrees.
    </td>   
  </tr>
</table>  

## Motor Drivers

The Hexpod robot requires a way to connect a large number of servo motors to a microcontroller with limit IO pins. To achieve this we use a pair of Adafruit [PCA9685 16-channel 12-bit servo motor drivers](https://cdn-learn.adafruit.com/downloads/pdf/16-channel-pwm-servo-driver.pdf). These motor drivers have their own onboard NXP Semiconductors [PCA9685 microcontroller](http://www.adafruit.com/datasheets/PCA9685.pdf) that handles the details of PWM signalling to the motors so all we have to do is communicate to them via I2C which only consumes 2 IO pins. The defult I2C address for the driver is 64 (0x40). There is also an all-call address at 112 (0x70). Since hexBot has 18 motors and a single driver can only handle a maximum of 16 we need to use 2 of these drivers. Since both drivers are on the same I2C bus we need to change the I2C address of the second driver to avoid conflicts. Page 13 of the Adafruit document explains how to do this.  

## Line level converter

Since the ESP32 microprocessor used for Hexbot's brain is a 3.3VDC device and the PCA9685 microprocessor used in the motor driver board is a 5 VDC device we must use a line level converter on the I2C bus to connect between them. Hexbot uses the KeeYees [4 Channel I2C Logic Level Converter Bi-Directional Module](https://www.amazon.ca/gp/product/B07LG646VS/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1). 

## Assembly
Full step by step instructions for Hexbot can be found [here](hexbotAssembly.md).
