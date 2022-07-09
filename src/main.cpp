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
  client.publish("esp32/test", "Hello from ESP32");
}

void loop() {
  client.loop();
  Serial.println(client.state());
  client.publish("esp32/test", "Hello from ESP32");
  delay(10000);

}