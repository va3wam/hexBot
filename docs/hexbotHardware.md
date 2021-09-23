# Hexbot Hardware

This page lists all the parts that you need in order to build your own Hexbot. 

## Chassis

Hexbot's chassis is comprised of a lower main body section with six protruding legs and a PCB mounted on top. The body and legs are milled out of 6061 extruded aluminium. When pully assembed Hexbot's physical dimensions are roughly:

* Height = ~ 5 inches when in neutral standing position.
* Length = ~ 14 inches when in neutral standing position.
* Weight = ~ 3 lbs 7.5 Oz without battery or PCB.

Hexbot's chassis is comprised of 1 lower body panel, 6 hip components, 6 upper leg components and 6 lower leg components. *Note that you will need to fabricate your own upper body component used for mounting the electronics*.   

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/newLowerBody v7.png" alt="Main body" width="100" height="100">
          <figcaption>Fig.1 - Main body</figcaption>
       </figure> 
    </td>
  </tr>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/newHip v12.png" alt="Hip" width="100" height="100">
          <figcaption>Fig.2 - Hip</figcaption>
       </figure> 
    </td>
  </tr>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/upperLeg v5.png" alt="Upper leg" width="100" height="100">
          <figcaption>Fig.3 - Upper leg</figcaption>
       </figure> 
    </td>
  </tr>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/newLowerLeg v10.png" alt="Lower leg" width="100" height="100">
          <figcaption>Fig.4 - Lower leg</figcaption>
       </figure> 
    </td>
  </tr>
</table>  

## Micellaneous Hardware

In addition to the parts above you will also need 

* 72 [M3 0.5 x 10 cap head screws](https://www.amazon.ca/gp/product/B07FDLN8C3/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
* 64 [M3 nuts](https://www.amazon.ca/gp/product/B07FDLN8C3/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
* 18 [Mallofusa 25 tooth Servo Horn](https://www.amazon.ca/Mallofusa-Servo-Aluminum-Silvery-Helicopter/dp/B00NOGMK3M). 
* 18 M3 0.5 x6 button head screws (come with the horns). 
 
## Motors

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/mg996r-towerpro-servo-motor.jpg" alt="servo motor" width="100" height="100">
          <figcaption>Fig.5 - Servo motor</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       Hexbot has a total of 18 leg joints. These leg joints are 
       <a href="https://components101.com/motors/mg996r-servo-motor-datasheet">MG996R Servo motors</a>. The applied voltage of this motor should be in range of 4.8 to 7.2V. The frequency of motor is 50 Hz and the PWM duty cycle is 20 milliseconds. This motor has 3 pins as follows:
      <ul>
         <li>PWM: Orange</li>
         <li>VCC: Red</li>
         <li>GND: Brown</li>
      </ul>
    </td>   
  </tr>
</table>  

## Servo Horns

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/servo-horn.jpg" alt="servo horn" width="100" height="100">
          <figcaption>Fig.6 - Servo horn</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       Each servo motor requires an 
       <a href="https://www.amazon.ca/gp/product/B00NOGMK3M/ref=ppx_yo_dt_b_asin_title_o04_s00?ie=UTF8&psc=1">aluminium round servo horn with a 25 tooth spline</a>. 
    </td>   
  </tr>
</table>  

## Motor Drivers

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/pca9685-16-channel-12-bit-pwm-servo-driver_1.jpg" alt="motor driver" width="100" height="100">
          <figcaption>Fig.7 - Motor driver</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       The Hexpod robot requires a way to connect a large number of servo motors to a microcontroller with limit IO pins. To achieve this we use a pair of Adafruit <a href="https://cdn-learn.adafruit.com/downloads/pdf/16-channel-pwm-servo-driver.pdf">PCA9685 16-channel 12-bit servo motor drivers</a>. These motor drivers have their own onboard NXP Semiconductors <a href="http://www.adafruit.com/datasheets/PCA9685.pdf">PCA9685 microcontrollers</a> that handles the details of PWM signalling to the motors so all we have to do is communicate to them via I2C which only consumes 2 IO pins. The defult I2C address for the driver is 64 (0x40). There is also an all-call address at 112 (0x70). Since hexBot has 18 motors and a single driver can only handle a maximum of 16 we need to use 2 of these drivers. Since both drivers are on the same I2C bus we need to change the I2C address of the second driver to avoid conflicts. Page 13 of the Adafruit document explains how to do this.     
    </td>   
  </tr>
</table>  

## Line level converter

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/voltageLevelConverter.jpg" alt="motor driver" width="100" height="100">
          <figcaption>Fig.8 - I2C bus voltage converter</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       Since the ESP32 microprocessor used for Hexbot's brain is a 3.3VDC device and the PCA9685 microprocessor used in the motor driver board is a 5 VDC device we must use a line level converter on the I2C bus to connect between them. Hexbot uses the KeeYees <a href="https://www.amazon.ca/gp/product/B07LG646VS/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1">4 Channel I2C Logic Level Converter Bi-Directional Module</a> which appears to be a clone of the Sparkfun Bi-Directional Logic Level Converter. For wiring help check out the <a href="https://learn.sparkfun.com/tutorials/bi-directional-logic-level-converter-hookup-guide/all">wiring guide</a>. 
    </td>   
  </tr>
</table>  

## Main processor

<table>
  <tr>
    <td align ="left"> 
       <figure>
          <img src="/img/esp32-board-bg.jpg" alt="ESP32 dev board" width="100" height="100">
          <figcaption>Fig.9 - ESP32 Dev Board</figcaption>
       </figure> 
    </td>
    <td align ="left"> 
       The brains of Hexbot come courtesy of an Espressif <a href="https://va3wam.github.io/soc/technology%20stack/architecture/SOC-Technology-Stack/">ESP32</a> Software On a Chip (SOC). We are using Zerynth's 30 pin variant of their <a href="https://testzdoc.zerynth.com/reference/boards/doit_esp32/docs/">DOIT Esp32 DevKit v1</a> development board for ESP32 integration into our circuit.  
    </td>   
  </tr>
</table>  

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
