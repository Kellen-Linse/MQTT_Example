#include "mqtt.h"

// Variables
  WiFiClientSecure net = WiFiClientSecure();
  MQTTClient client = MQTTClient(256);

// Functions 

// Initialize MQTT
void mqttSetup(){
  connectAWS();
}

// Check the connection and run the MQTT client related code 
void mqttLoop(){
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

// This function will be ran when we wish to publish a message
// It will take data and turn it into a JSON doc prior to sending the 
// data to the MQTT broker (AWS IoT)
// This could be broken out and expanded as the programs complexity grows.
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

// This function handles incoming messages which are received in JSON format 
// It first decodes the JSON, then acts depending on the incoming data.
// This could be broken out and expanded as the programs complexity grows.
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

// Connect to AWS, this requires certifications set up in AWS IoT core prior to connecting
void connectAWS(){
  // Configure WiFiClientSecure to use the AWS IoT device credentials
  // These certs can be found in the "secrets.h" file. 
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

// Handle reconnecting to the broker if the connection is lost
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
