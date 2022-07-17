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
  client.publish("esp32test/test", "Startlog");




  touch_pad_init();
  touch_pad_set_voltage(TOUCH_HVOLT_2V4, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V);
  touch_pad_config(TOUCH_PAD_NUM2, 0);



}

void loop() {

  
  uint16_t value;                // = touchRead(T2);
  touch_pad_read(TOUCH_PAD_NUM2, &value);
  char payload[16];
  itoa(value, payload, 10);

  Serial.println(value);

  client.loop();
  Serial.println(client.state());
  client.publish("esp32test/moisture", payload);


  int RSSI = WiFi.RSSI();
  Serial.print("RSSI: ");
  Serial.println(RSSI);
  char RSSIChar[16];
  itoa(RSSI, RSSIChar, 10);
  client.publish("esp32test/RSSI", RSSIChar);


  delay(2000);
}