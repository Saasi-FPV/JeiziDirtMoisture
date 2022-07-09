#include <Arduino.h>


int TimeToSleep = 10 * 1000000;


void setup() {
  Serial.begin(115200);
  delay(1000);
  esp_sleep_enable_timer_wakeup(TimeToSleep);

  pinMode(2, OUTPUT);
  pinMode(A5, INPUT);

  Serial.println("Bi Wach");
  digitalWrite(2, HIGH);


  for(int i = 0; i < 10; i++){
    float tempVal = analogRead(A5);
    Serial.print("RAW ADC");
    Serial.println(tempVal);
    tempVal = (tempVal * 3.3) / 4096;
    Serial.print("ADC misst mist?: ");
    Serial.println(tempVal);
  }



  delay(1000);
  Serial.println("Gang ga Schl...ZZZZZZZZZZZ");
  esp_deep_sleep_start();




}

void loop() {
  // put your main code here, to run repeatedly:
}