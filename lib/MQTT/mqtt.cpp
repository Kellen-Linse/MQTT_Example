#include "mqtt.h"

WiFiClient espClient;
PubSubClient client(espClient);

const char* mqtt_server = "broker.mqttdashboard.com";
long lastMsg = 0;
char msg[50];
int value = 0;

void mqttSetup(){
    // MQTT
  client.setServer(mqtt_server, 1883);
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

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "Kellen_esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("turning led on");
      digitalWrite(ledPin, HIGH);
    }
    else if(messageTemp == "off"){
      Serial.println("turning led off");
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("Kellen_ESP32")) {
      Serial.println("connected");
      
      client.subscribe("Kellen_esp32/output"); // Subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}