![hexaBot](img/hexbotBanner.png)

[![LICENSE](https://img.shields.io/badge/license-MIT-lightgrey.svg)](https://raw.githubusercontent.com/mmistakes/minimal-mistakes/master/LICENSE)

This repository contains the Arduino source code that runs on an embedded processor at the heart of the six legged robot we call HexaBot. The goals of this project can be found [here](goals.md). 

---

## Getting Started

This project require you to have a Hexbot robot. The Robot is made up of a custom robot chassis and PCB as well as the code in this repository. Without a version 3 or later Hexbot robot this code will not be very useful to you. 

### Prerequisites

In order to make use of the code in this repository you will require the following items.

* A [Hexbot chassis](doc/hexbotHardware.md).
* The [Hexbot custom PCB](doc/hexbotCircuit.md).
* An [MQTT broker](doc/MQTTbroker.md).

Additionally, if you wish to contribute code to this project you should review this material.

* The software development stack that we use is explained [here](https://va3wam.github.io/software/). 
* Our coding standards and practices are laid out [here](https://va3wam.github.io/software/#standards).  

### Installing

A set of instructions on how to install the source code for VA3WAM projects can be found [here](https://va3wam.github.io/versionControl/). 

### Documentation

``` Maintain a list of links to the documentation found in this repository here.```

## Running the tests

At this time we have no tools or standards for automated testing of Arduino code on an embedded system. 

## Deployment

At this time we use serial over USB to load the inital code onto the embedded system. Subsequent builds can be uploaded using serial over USB or in some cases use an web interface to do [OTA](https://en.wikipedia.org/wiki/Over-the-air_programming) updates.

## Built With

  - [Visual Studio Code](https://code.visualstudio.com/) - Text editor.
  - [PlatformIO](https://platformio.org/) - IDE for ESP32 based Arduino development.

## Contributing

Please read [CONTRIBUTING.md](contributing.md) for details on our code
of conduct, and the process for submitting pull requests to us.

## Versioning

We use [Semantic Versioning](http://semver.org/) for versioning. For the versions
available, see the [tags on this
repository](https://github.com/va3wam/hexaBot/releases). 

## Authors

  - **Old Squire**
  - **Doug Elliott**

## License

This project is licensed under the [MIT License](license.md)

## Acknowledgments

  - Robot chassis design inspired by [Cameron Buss' Swampy the Hexapod](https://grabcad.com/library/swampy-the-hexapod-1). 
