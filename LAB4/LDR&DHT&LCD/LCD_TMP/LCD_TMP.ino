#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#define SW1 2
#define SW2 3 
bool sw1State = 0;
unsigned long previousPress;
unsigned long previousTimeMode;
unsigned long currentTime;
uint8_t Mode = 1;
DHT dht(7, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long previousTime;
uint8_t second = 0;
uint8_t minute = 0;
uint8_t hour = 0;

uint8_t second_F;
uint8_t second_S;
uint8_t minute_F;
uint8_t minute_S;
uint8_t hour_F;
uint8_t hour_S;

void setup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  attachInterrupt(0, button1, FALLING);  
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(6, 0); lcd.print(":");
  lcd.setCursor(9, 0); lcd.print(":");
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

// GEN TIME
void generateTime() {
  currentTime = millis();
  if(currentTime - previousTime > 1000) {
    previousTime = currentTime;
    second++;
    if(second >= 60) {
      second = 0;
      minute++;
    }
    
    if(minute >= 60) {
      minute = 0;
      hour++;
    }

    if(hour >= 24) {
      hour = 0;
    }
  }
  else{
    if(currentTime < previousTime) previousTime = 0;
  }
}

void LatchTime() {
  analyzeUnit();
  lcd.setCursor(4, 0); lcd.print(hour_F);
  lcd.setCursor(5, 0); lcd.print(hour_S);
  lcd.setCursor(7, 0); lcd.print(minute_F);
  lcd.setCursor(8, 0); lcd.print(minute_S);
  lcd.setCursor(10, 0); lcd.print(second_F);
  lcd.setCursor(11, 0); lcd.print(second_S);
}

uint8_t separateFirstBit(uint8_t data) {
  if(data >= 10) return data / 10;
  else return 0;
}

uint8_t separateSecBit(uint8_t data) {
  return data % 10;
}

void analyzeUnit() {
  second_F = separateFirstBit(second);
  second_S = separateSecBit(second);

  minute_F = separateFirstBit(minute);
  minute_S = separateSecBit(minute);

  hour_F = separateFirstBit(hour);
  hour_S = separateSecBit(hour);
}


int data;
uint8_t level;
void loop() {
  generateTime();
  LatchTime();
  selectMode();
  data = analogRead(A0);
  if (data >= 400 && data < 500) level = 0;
  else if (data >= 500 && data < 600) level = 1;
  else if (data >= 600 && data < 700) level = 2;
  else if (data >= 700 && data < 800) level = 3;
  else if (data >= 800 && data < 900) level = 4;
  else if (data >= 900) level = 5;
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (isnan(h) || isnan(t)) return;
//    map(data, 400, 1000, 0, 100);

  if(Mode == 1) {
    lcd.setCursor(0, 1); lcd.print("Temperature");
    lcd.setCursor(15, 1); lcd.print("C");
    lcd.setCursor(12, 1); lcd.print(String(t));
  }

  if(Mode == 2) {
    lcd.setCursor(0, 1); lcd.print("Humidity");
    lcd.setCursor(15, 1); lcd.print("%");
    lcd.setCursor(12, 1); lcd.print(String(h));
  }

  if(Mode == 3) {
    lcd.setCursor(0, 1); lcd.print("Brightness");
    lcd.setCursor(15, 1); lcd.print("%");
    lcd.setCursor(12, 1); lcd.print(String(map(data, 400, 1000, 0, 100)));
  }



}
