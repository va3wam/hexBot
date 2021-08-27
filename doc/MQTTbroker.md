# MQTT Broker

The Hexbot robot can be remotely controlled via MQTT messaging over a 2.4GHz WiFi link. This means that you must have a QOS1 capable MQTT broker on your network. 

## MQTTfx
We use the MQTTfx client to issue commands to Hexbot.

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
