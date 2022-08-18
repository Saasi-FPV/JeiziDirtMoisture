#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "chjasipa";
const char* password = "0661114160";
const char* mqttServer = "mqtt.tanglehive.org";
const int mqttPort = 1883;
const char* mqttUser = "jeizimqtt";
const char* mqttPassword = "aayEwsyqbxsS7re";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword )) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }




  touch_pad_init();
  touch_pad_set_voltage(TOUCH_HVOLT_2V4, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
  touch_pad_config(TOUCH_PAD_NUM2, 0);



}

void loop() {

  client.loop();
  Serial.println(client.state());

  
  uint16_t value;
  char valueChar[16];
  touch_pad_read(TOUCH_PAD_NUM2, &value);
  itoa(value, valueChar, 10);
  Serial.print("Messwert: ");
  Serial.println(value);
  client.publish("Sensor1/moisture", valueChar);


  int RSSI;
  char RSSIChar[16];
  RSSI = WiFi.RSSI();
  itoa(RSSI, RSSIChar, 10);
  Serial.print("RSSI: ");
  Serial.println(RSSI);
  client.publish("Sensor1/RSSI", RSSIChar);


  delay(2000);
}