#include <Arduino.h>


int TimeToSleep = 10 * 1000000;


void setup() {
  Serial.begin(115200);
  delay(1000);
  esp_sleep_enable_timer_wakeup(TimeToSleep);

  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.flush();
  Serial.println("Bi Wach");
  delay(1000);
  Serial.println("Gang ga Schl...ZZZZZZZZZZZ");
  esp_deep_sleep_start();




}

void loop() {
  // put your main code here, to run repeatedly:
}