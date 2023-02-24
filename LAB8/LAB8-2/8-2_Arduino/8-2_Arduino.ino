#include <SoftwareSerial.h>
#include "DHT.h"

SoftwareSerial ar(9, 10);
DHT dht(7, DHT22);

void setup() {
  Serial.begin(9600);
  ar.begin(9600);
  dht.begin();
}

void pushHum(){
  float h = dht.readHumidity();
  if (isnan(h)) return;
  ar.print('H'); ar.print(h); ar.print("_");

  // Serial.print('H'); Serial.print(h); Serial.println("_");
}
 
void pushTemp(){
  float t = dht.readTemperature();
  if (isnan(t)) return;
  ar.print('T'); ar.print(t); ar.print("_");

  // Serial.print('T'); Serial.print(t); Serial.println("_");
}

void loop() {
  if(ar.available() > 0) {
    char text = ar.read();
    if(text == 'h') {
      pushHum();
    }
    else if(text == 't') {
      pushTemp();
    }
  }
}
