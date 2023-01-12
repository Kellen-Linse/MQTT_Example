#include "mqtt.h"

// Variables
  WiFiClientSecure net = WiFiClientSecure();
  MQTTClient client = MQTTClient(256);

// Functions 

void mqttSetup(){
  connectAWS();
}

void mqttLoop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void publishMessage(){
  StaticJsonDocument<200> doc;
  doc["time"] = millis();
  doc["Message"] = "Hello From ESP32!";
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);
  Serial.print("PUBLISHING: ");
  Serial.println(jsonBuffer);
  
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("INCOMING: " + topic + " - " + payload);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["message"];

  // If a message is received on the AWS_IOT_SUBSCRIBE_TOPIC topic, 
  // this will check if the message is either "on" or "off" 
  // changing the output state according to the message.
  if (topic == AWS_IOT_SUBSCRIBE_TOPIC) {
    if(strcmp(message, "on") == 0){
      Serial.println("Turning LED on");
      digitalWrite(ledPin, HIGH);
    }
    else if(strcmp(message, "off") == 0){
      Serial.println("Turning LED off");
      digitalWrite(ledPin, LOW);
    }
  }
}

// 
void connectAWS(){
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT...\n");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
  delay(200);
}

void reconnect() {
  // Attempt to connect
  Serial.print("Attempting Reconnection to AWS IOT...\n");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(300);
  }

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    delay(2000);
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);
  Serial.println("AWS IoT Reconnected!");
}
