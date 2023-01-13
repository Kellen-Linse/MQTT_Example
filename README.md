# ESP32 MQTT Example Repository

- This repo contains functional examples for connecting an ESP32 to both AWS IoT Core and HiveMQ's test broker.
- The ESP32 can send messages via a momentary push button wired to `GPIO4`
- The ESP32 can receive messages from either broker turning on or off the built in LED on `GPIO2`

> Please see either the `AWS_IoT` branch or the `HiveMQ` branch for reference.

## Wiring Diagram for ESP32

- Note the diagram does not show a built in LED so an external LED has been added for reference.

![ESP32](./resources/ESP32.JPG)