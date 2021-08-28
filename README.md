![hexaBot](img/hexbotBanner.png)

[![LICENSE](https://img.shields.io/badge/license-MIT-lightgrey.svg)](https://raw.githubusercontent.com/mmistakes/minimal-mistakes/master/LICENSE)

This repository contains the Arduino source code that runs on an embedded processor at the heart of the six legged robot we call HexBot. The goals of this project can be found [here](goals.md). 

## Getting Started

This project requires that you have a Hexbot robot. The Robot is made up of a custom robot chassis and PCB as well as the code in this repository. Without a version 3 or later Hexbot robot this code will not be very useful to you. 

### Prerequisites

In order to make use of the code in this repository you will require the following items.

* A [Hexbot chassis](doc/hexbotHardware.md).
* The [Hexbot custom PCB](doc/hexbotCircuit.md).
* An [MQTT broker](doc/MQTTbroker.md) used by the robot's [MQTT web interface](doc/hexbotWebInterface.md).

### Code Compatability

The Arduino C++ code was written to run on the Espressif ESP WROOM32 "Software On a Chip" (SOC). The development board used for this SOC is the Adafruit Huzzah32 featherboard. Note that some standard Arduino functions such as AnalogWrite() have not been implemented on the ESP32 SOC and alternate functions such as ledcSetup(), ledcAttachPin() and ledcWrite() must be used in their place. There are some additional compatability issues of note as follows:

* The GPIO pin usage is loosey Adafruit featherboard compliant meaning it will work with some boards such as the Adafruit OLED featherboard.
* This code will NOT run on an ESP8266 unmodified because of both GPIO incompatability as well as some ESP32 specific libraries that are in use.

### Installing

A set of instructions on how to install the source code for VA3WAM projects can be found [here](https://va3wam.github.io/versionControl/). 

### Documentation

Here is an index of links to helpful documents found in this repository.

* Sample [platformio.ini](AA/platformIO-MAC-example.txt) template.

## Testing

At this time we have no tools or standards for automated testing of Arduino code on an embedded system. 

## Deployment

Use serial over USB to load the inital code onto the embedded system. Subsequent builds can be uploaded using either serial over USB or 
a [OTA web interface](webOTA.md) hosted by the robot which allows you to do [OTA](https://en.wikipedia.org/wiki/Over-the-air_programming) updates.

## Built With

* [Visual Studio Code](https://code.visualstudio.com/) - Text editor.
* [PlatformIO](https://platformio.org/) - IDE for ESP32 based Arduino development.

## Contributing

Please read [CONTRIBUTING.md](contributing.md) for details on our code
of conduct, and the process for submitting pull requests to us.

## Versioning

We use [Semantic Versioning](http://semver.org/) in naming the [releases](https://github.com/va3wam/hexaBot/releases) of this code base. 

## Authors

* **[Old Squire](https://github.com/theagingapprentice)**
* **[Doug Elliott](https://github.com/nerdoug)**

## License

This project is licensed under the [MIT License](license.md).

## Acknowledgments

* Robot chassis design inspired by [Cameron Buss' Swampy the Hexapod](https://grabcad.com/library/swampy-the-hexapod-1).
* 3 DOF Inverse Kinematic code inspired by [Avatar
Aymen Nacer](https://github.com/AymenNacer/Forward-and-Inverse-Kinematics-for-3-DOF-Robotic-arm). 
* Tony DiCola and Adafruit Industries for their MQTT QOS1 Arduino library.
* Jeff Rowberg for the MPU6050 DMP logic. ```May not use.```
* DFRobot & John Rickman for their LiquidCrystal I2C LCD display Arduino library. ```May not use.```
* The many folks involved in porting the Arduino libraries over to the ESP32.
