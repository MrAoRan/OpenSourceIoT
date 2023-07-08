/*
Author:AoRan
Program name:Smart Lamp based on NodeMCU
Programming date:2023/3/916:49
Program's goal:Use the NodeMCU and servo to control the lamp's switch in living room.
Besides,it was supported by Bemfa and MQTT to connect with Mi family and be called
by XiaoAi.
Elements in need:A NodeMCU,a 9g servo(May less than 9g even.),some wires.
*/

#include <Arduino.h>
#include <Servo.h>//importing Servo library files to drive the servo.
#include <ESP8266WiFi.h>//improting for wiFi functions.
#include "PubSubClient.h"//importing for MQTT functions.

const char* ssid = "ChinaNet-18CC";//WiFi's name.
const char* password = "12345678";//WiFi's password.
#define ID_MQTT "ddc260009946495593f1d9afdc64bc78"//User's personal key.
const char* topic ="light002";//Topic's name,need to create first.
String updateUrl = "";//.bin firmware updating net.
static const int ServoPin = D1;//Servo's signal pin.
Servo servo;//Creating a servo object called servo.

const char* mqtt_server = "bemfa.com";//Bemfa MQTT server.
const int mqtt_server_port = 9501;//Bemfa MQTT server's port.
WiFiClient espClient;
PubSubClient client(espClient);


void ServoOn() { //The function driving servo to turn on switch.
  Serial.println("Drove the servo on.");
  servo.write(15);

}

void ServoOff() {//The function driving servo to turn off switch.
  Serial.println("Drove the servo on.");
  servo.write(-15);
}

void connect_wifi() {//The function repeat connecting to WiFi until succeeded.
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Topic:");
  Serial.println(topic);
  String msg = "";
  for (int i = 0; i < length; i++) {
    msg += (char)payload[i];
  }
  Serial.print("Msg:");
  Serial.println(msg);
  if (msg == "on") {//If received the word "on".
    ServoOn();//Execute the ServoOn function.
  } else if (msg == "off") {//If received the word "off".
    ServoOff();//Execute the ServoOff function.
  }
  msg = "";
}

void reconnect(){//The function looping until reconnected.
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ID_MQTT)) {
      Serial.println("connected");
      Serial.print("subscribe:");
      Serial.println(topic);
      client.subscribe(topic);//Subscribe the topic,could write multi commands to subscribe multi topics.
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}


void setup() {
  servo.attach(ServoPin);//Attach the servo's pin to ServoPin.
  Serial.begin(115200);//Setting the band rate to 115200,which was special for NodeMCU.     
  connect_wifi();//Connecting to our WiFi.           
  client.setServer(mqtt_server, mqtt_server_port);//Connecting to the MQTT server.
  client.setCallback(callback); 
}


void loop() {
  if (!client.connected()){//Keeping reconnecting if connected failed. 
  reconnect();
  }
  client.loop();
}

