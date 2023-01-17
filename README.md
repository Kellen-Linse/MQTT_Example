# MQTT Example - AWS

> MQTT Example connecting to AWS IoT Core

## Reference 

  - [Building an AWS IoT Core device using AWS Serverless and an ESP32](https://aws.amazon.com/blogs/compute/building-an-aws-iot-core-device-using-aws-serverless-and-an-esp32/)

## Libraries Used:

  - **MQTT** by Joel Gaehwiler.
  - **ArduinoJson** by Benoit Blanchon

## Additional Files Needed:

- credentials.h

```C
# pragma once

// Wifi
const char* ssid = "YOUR_SSID_HERE"; 
const char* password = "YOUR_PASSWORD_HERE";
```

- secrets.h

> Fill these values in with the values you receive in the "Create things" section in the AWS IoT console. See the reference link above for more details.

```C
#include <pgmspace.h>

#define SECRET
#define THINGNAME "YourThingName"

const char AWS_IOT_ENDPOINT[] = "xxxxx.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
-----END CERTIFICATE-----
)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
-----END RSA PRIVATE KEY-----
)KEY";
```
=======
# ESP32 MQTT Example Repository

- This repo contains functional examples for connecting an ESP32 to both AWS IoT Core and HiveMQ's test broker.
- The ESP32 can send messages via a momentary push button wired to `GPIO4`
- The ESP32 can receive messages from either broker turning on or off the built in LED on `GPIO2`

> Please see either the `AWS_IoT` branch or the `HiveMQ` branch for reference.

## Wiring Diagram for ESP32

- Note the diagram does not show a built in LED so an external LED has been added for reference.

![ESP32](./resources/ESP32.JPG)
