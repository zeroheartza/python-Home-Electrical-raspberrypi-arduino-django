/*
 * ESP8266 (Adafruit HUZZAH) Mosquitto MQTT Publish Example
 * Thomas Varnish (https://github.com/tvarnish), (https://www.instructables.com/member/Tango172)
 * Made as part of my MQTT Instructable - "How to use MQTT with the Raspberry Pi and ESP8266"
 */

#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker
#include <PZEM004Tv30.h>

PZEM004Tv30 pzem(5, 4);

const int ledPin = 0; // This code uses the built-in led for visual feedback that the button has been pressed
const int buttonPin = 13; // Connect your button to pin #13

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "heart";
const char* wifi_password = "heart650";

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "192.168.1.102";
const char* mqtt_topic = "test";
const char* mqtt_username = "username";
const char* mqtt_password = "heart650";
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "node1";

// Initialise the Pushbutton Bouncer object


// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

void setup() {
 



  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
  
}

void loop() {
    char result[8];
    
//    float energy = pzem.energy();
//    Serial.print("Energy: "); Serial.print(energy,3); Serial.println("kWh");
//    dtostrf((energy,3), 6, 2, result); 

    float power = pzem.power();
    dtostrf(power, 6, 2, result); 
    Serial.print("Power: "); Serial.print(result); Serial.println("W");
  
    if(isnan(power)){
        Serial.println("Error reading power");
    } 
    else {
        
          if (client.publish(mqtt_topic, result)) {
                Serial.println("message sent success!");
          }

          else {
                Serial.println("Message failed to send. Reconnecting to MQTT Broker and trying again");
                client.connect(clientID, mqtt_username, mqtt_password);
      
                 client.publish(mqtt_topic,result);
          }
    }
   
    delay(60000);
  

}
