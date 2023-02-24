#include "DHT.h"
unsigned long previousTime;
unsigned long currentTime;
DHT dht(2, DHT22);
#define led1 8
#define led2 9
#define led3 10
#define led4 11
#define led5 12
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  Serial.begin(9600);
  dht.begin();
}

void activeLED(uint8_t c) {
  if (c == 0){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  else if(c == 1){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  else if(c == 2){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  else if(c == 3){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
  }
  else if(c == 4){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, HIGH);
  }
  else if(c == 5){
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }  
}

int data;
uint8_t level;
void loop() {
  data = analogRead(A0);
  currentTime = millis();
  if (currentTime - previousTime >= 2000) {
    previousTime = currentTime;
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.print("Humidity: ");
    Serial.print(h, 2);
    Serial.print("%  Temperature: ");
    Serial.print(t, 2);
    Serial.print(" C ");
    Serial.print("Brightness ");
    Serial.print(map(data, 400, 1000, 0, 100));
    Serial.println("%");
  }

  if (data >= 400 && data < 500) level = 0;
  else if (data >= 500 && data < 600) level = 1;
  else if (data >= 600 && data < 700) level = 2;
  else if (data >= 700 && data < 800) level = 3;
  else if (data >= 800 && data < 900) level = 4;
  else if (data >= 900) level = 5;

  activeLED(level);
  

}
