#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
SoftwareSerial espSerial(D7,D6);

// Update these with values suitable for your network.

const char* ssid = "AndroidAP";
const char* password = "0987654321";
const char* mqtt_server = "test.mosquitto.org";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];


void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      delay(10000);
    }
  }
}

void setup() {
  espSerial.begin(115200);
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
 String  alldata = espSerial.readString();
String sub = alldata.substring(0, 4);
Serial.println(sub);
String sub1 = alldata.substring(7, 11);
Serial.println(sub1);
String sub2 = alldata.substring(14, 18);
Serial.println(sub2);
String sub3 = alldata.substring(21, 25);
Serial.println(sub3);
String sub4 = alldata.substring(28, 33);
Serial.println(sub4);
float v1 = sub.toFloat();
float v2 = sub1.toFloat();
float v3 = sub2.toFloat();
float v4 = sub3.toFloat();
float T1 = sub4.toFloat();
    snprintf (msg, MSG_BUFFER_SIZE, "BMS DATA V1 - #%f",  v1);
    client.publish("rj", msg);
    snprintf (msg, MSG_BUFFER_SIZE, "BMS DATA V2- #%f",  v2);
    client.publish("rj", msg);
    snprintf (msg, MSG_BUFFER_SIZE, "BMS DATA V3- #%f",  v3);
    client.publish("rj", msg);
    snprintf (msg, MSG_BUFFER_SIZE, "BMS DATA V4- #%f",  v4);
    client.publish("rj", msg);
    snprintf (msg, MSG_BUFFER_SIZE, "BMS DATA Temp- #%f",  T1);
    client.publish("rj", msg);
  }
  delay(5000);
}
