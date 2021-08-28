# MQTT Broker

The Hexbot robot acts as an IoT Smart [Connected Product/Device](https://en.wikipedia.org/wiki/Smart_device).

## Communication
Hexbot features a 2.4GHz 802.11n WiFi radio that requires a WiFi access point capable of communicating at 150Mbps. You must also have a QOS1 capable MQTT broker listening on port 1883 on your network. Additionally, you must configure the MQTT Broker to support websocket connection on port 9001. Finally you must have a client device capable of running a web browser. This enables the robot to be remotely controlled via MQTT messaging over a WiFi link.

### MQTT Interface
Hexbot acts as an [MQTT](https://en.wikipedia.org/wiki/MQTT) client and supports a PUB/SUB interface that listens for messages on port 1883 encapsulated in IPv4 packets. The robot publishes and subscribes to/from topics via a broker usiing QOS1 MQTT messages encapsulated in TCP/IP packets. 

## MQTT Client
We use the MQTTfx client on out computer to issue [commands](mqttCommands.md) to Hexbot.

## Raspberry Pi Hosting Server
We host the MQTT on a Rapsberry Pi 3 Model B V1.2. 

```
cat /etc/os-release
PRETTY_NAME="Raspbian GNU/Linux 10 (buster)"
NAME="Raspbian GNU/Linux"
VERSION_ID="10"
VERSION="10 (buster)"
VERSION_CODENAME=buster
```

## Mosquitto Broker Software
We run the Mosquitto MQTT broker as a background daemon configured as follows.

```
mosquitto version 1.5.7 starting
1630104172: Using default config.
1630104172: Opening ipv4 listen socket on port 1883.
```

### Identification
The unqiue Media Access Control or [MAC](https://en.wikipedia.org/wiki/Medium_access_control) address of the radio prefixed by 'hexbot' is used to uniquely identify each hexbot robot to both the required WiFi Access Point and the MQTT broker. This makes it possible for multiple robots to co-exist in the same network.
