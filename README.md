# ESP32 MQTT Example Repository

> **Please see either the `AWS_IoT` branch or the `HiveMQ` branch for reference.**

<br>

- This repo contains functional examples for connecting an ESP32 to both **AWS IoT Core** and **HiveMQ's** test broker.
- The ESP32 can send messages via a momentary push button wired to `GPIO4`
- The ESP32 can receive messages from either broker turning on or off the built in LED on `GPIO2`


## Wiring Diagram for ESP32

- Note the diagram does not show a built in LED so an external LED has been added for reference.
- The built in LED is often on `GPIO2` or `GPIO13` check your boards layout or you can wire an LED as shown here.

![ESP32](./resources/ESP32.JPG)

## Additional Files and Libraries

- Please see the readme for each of the individual branches for additional files and libraries needed for this project.