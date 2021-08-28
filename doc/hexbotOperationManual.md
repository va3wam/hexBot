# Hexbot Operation Manual

This page contains information useful when servicing or operating Hexbot.

## Code Updates

Code updates can be done in one of two ways. First, they can be done via a local USB micro conection. Here are the steps to do that.

```Put steps here```.

Code updates can also be updated Over-The-Air (OTA) using Hexbot's web interface. Details on how this is done can be found [here](webOTA.md).
 
## Data Analytics

Monitoring and dynamic configuration of Hexbot is done via MQTT messages between the web browser client and the robot. The robot outputs two types of data. One is health data in the form of error counts for various events of interest. The second is telemetry data which provides real time sensor data regarding the balancing activities of the robot. The documenation for these messages is maintained within the code itself and is extracted [here]() via Doxygen during merging of code into the main branch of the repository. 
