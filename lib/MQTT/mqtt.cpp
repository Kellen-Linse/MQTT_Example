#include "mqtt.h"

// Variables
  long lastMsg = 0;
  char msg[50];
  int value = 0;

  WiFiClientSecure net = WiFiClientSecure(); //
  MQTTClient client = MQTTClient(256); //

// Functions 

void mqttSetup(){
    // MQTT
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
  serializeJson(doc, jsonBuffer); // print to client
  Serial.print("PUBLISHING: ");
  Serial.println(jsonBuffer);
  
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

//  StaticJsonDocument<200> doc;
//  deserializeJson(doc, payload);
//  const char* message = doc["message"];
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
  Serial.print("Attempting MQTT connection...\n");
  Serial.print("Connecting to AWS IOT\n");

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
  Serial.println("AWS IoT Connected!");
}


// ========= unused =========

// void callback(char* topic, byte* message, unsigned int length) {
//   Serial.print("Message arrived on topic: ");
//   Serial.print(topic);
//   Serial.print(". Message: ");
//   String messageTemp;
  
//   for (int i = 0; i < length; i++) {
//     Serial.print((char)message[i]);
//     messageTemp += (char)message[i];
//   }
//   Serial.println();

//   // If a message is received on the topic Kellen_esp32/output, you check if the message is either "on" or "off". 
//   // Changes the output state according to the message
//   if (String(topic) == sub_topic_1) {
//     if(messageTemp == "on"){
//       Serial.println("Turning LED on");
//       digitalWrite(ledPin, HIGH);
//     }
//     else if(messageTemp == "off"){
//       Serial.println("Turning LED off");
//       digitalWrite(ledPin, LOW);
//     }
//   }
// }
