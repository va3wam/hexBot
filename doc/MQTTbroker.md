# MQTT Broker

Hexbot features a 2.4GHz WiFi radio, a WiFi access point, an MQTT broker and a client device capable of running a web browser. This enables the robot to be remotely controlled via MQTT messaging over a WiFi link. For this to work however, you must have a QOS1 capable MQTT broker on your network. 

## MQTT Client
In addition to the robot acting as an MQTT client we use the MQTTfx client on out computer to issue [commands](doc/mqttCommands.md) to Hexbot.

## Raspberry Pi
We host our MQTT broker as a service on a Rapsberry Pi 3 Model B V1.2. 

```
cat /etc/os-release
PRETTY_NAME="Raspbian GNU/Linux 10 (buster)"
NAME="Raspbian GNU/Linux"
VERSION_ID="10"
VERSION="10 (buster)"
VERSION_CODENAME=buster
```

## Mosquitto
We run Mosquitto as a background daemon configured as follows.

```
mosquitto version 1.5.7 starting
1630104172: Using default config.
1630104172: Opening ipv4 listen socket on port 1883.
```

### Identification
The unqiue media access control address of the radio prefixed by 'twipe' is used to uniquely identify each Twipe robot to both the required WiFi Access Point and the MQTT broker. This makes it possible for multipe robots to co-exist in the same network.

### Data Protocols
Communication between the robot and the MQTT broker is comprised of MQTT messaging on port 1883 encapsulated in IPv4 packets over a 2.4GHz 802.11n WiFi connection at 150Mbps. Communication between the MQTT broker and the web browser client is comprised of MQTT messages on port 1883 tunneled through a websocket connection on port 9001 encapsulated in IPv4 packets over whatever speed the local Access Point supports.  

### Device Management
Monitoring and dynamic configuration of the robot is done via MQTT messages between the web browser client and the robot. While not yet implemented the plan is to include Over-The-Air (OTA) for coe updates. Today code updates are done via a local USB micro conection.
---
