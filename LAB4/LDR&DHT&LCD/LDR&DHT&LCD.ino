#include "DHT.h"
#define SW1 2
#define SW2 3 
// Button Setting
bool sw1State = 0;
int buttonDeBounce = 200;
// times setting
unsigned long previousPress;
unsigned long previousTime;
unsigned long currentTime;
uint8_t Mode = 1;
DHT dht(7, DHT22);

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  attachInterrupt(0, button1, FALLING);  
  Serial.begin(9600);
  dht.begin();
}

void button1(){
  sw1State = 1;
}

void selectMode() {
  if (((millis() - previousPress) > 200) && sw1State) {
    previousPress = millis();
    if (digitalRead(SW1) == LOW) {
      if(Mode < 3 && Mode >= 1) {
        Mode++;
      }
      else {
        Mode = 1;
      }
      sw1State = 0;
    }
  }
}

int data;
uint8_t level;
void loop() {
  selectMode();
  data = analogRead(A0);
  if (data >= 400 && data < 500) level = 0;
  else if (data >= 500 && data < 600) level = 1;
  else if (data >= 600 && data < 700) level = 2;
  else if (data >= 700 && data < 800) level = 3;
  else if (data >= 800 && data < 900) level = 4;
  else if (data >= 900) level = 5;

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
  
}
