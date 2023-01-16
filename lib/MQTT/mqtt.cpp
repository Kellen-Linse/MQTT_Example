#include "mqtt.h"

// Variables
  WiFiClient espClient;
  PubSubClient client(espClient);
  long lastMsg = 0;
  char msg[50];
  int value = 0;

// Functions 

// Initialize MQTT
void mqttSetup(){
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

// Check the connection and run the MQTT client related code 
void mqttLoop(){
  if (!client.connected()) {
    Serial.println(client.connected());
    reconnect();
  }
  client.loop();
}

// This callback function will be run when the client receives a message from the broker
void callback(char* topic, byte* message, unsigned int length) {

  // Create a string from the given byte* message
  String messageTemp;
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }
  
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  Serial.print(messageTemp);
  Serial.println();

  // If a message is received on the topic Kellen_esp32/output, check if the message is either "on" or "off". 
  // Changes the output state of the LED pin according to the message
  // This could be broken out and expanded as the programs complexity grows.
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

// Handle reconnecting to the broker if the connection is lost
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