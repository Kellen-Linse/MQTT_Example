#include "mqtt.h"

// Variables

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// Functions 

void mqttSetup(){
    // MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void mqttLoop(){
  if (!client.connected()) {
    Serial.println(client.connected());
    reconnect();
  }
  client.loop();
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // If a message is received on the topic Kellen_esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == sub_topic_1) {
    if(messageTemp == "on"){
      Serial.println("Turning LED on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("Turning LED off");
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(clientID)) {
      Serial.println("connected");     
      client.subscribe(sub_topic_1); // Subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      delay(5000);
    }
  }
}