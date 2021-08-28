# Hexbot Operation Manual

This page contains information useful when servicing or operating Hexbot.

## Assembly
Full Hexbot assembly instructions can be found [here](hexbotAssembly.md).

## Code Updates

Code updates can be done in one of two ways. First, they can be done via a local USB micro conection. Here are the steps to do that.

```Put steps here```.

Code updates can also be updated Over-The-Air (OTA) using Hexbot's web interface. Details on how this is done can be found [here](webOTA.md).

## Configuring NVRAM

Certain environment specific values can be configured in NVRam avoidingg the need to rebuild and update code when the robot moves to a new network environment. Full details for this are found [here](hexbotConfigNVRAM.md).

## Data Analytics

Monitoring and dynamic configuration of Hexbot is done via MQTT messages between the web browser client and the robot. The robot outputs two types of data. One is health data in the form of error counts for various events of interest. The second is telemetry data which provides real time sensor data regarding the balancing activities of the robot. The documenation for these messages is maintained within the code itself and is extracted [here]() via Doxygen during merging of code into the main branch of the repository. ```Fix this link once we have Doxygen in place and pull requests automated.```
