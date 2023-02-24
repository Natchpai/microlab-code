
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial Node(D5, D6);
unsigned long Ttime = 0;
unsigned long Htime = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Node.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Temp");
  lcd.setCursor(0, 1); lcd.print("Humi");
  lcd.setCursor(15, 0); lcd.print("C");
  lcd.setCursor(15, 1); lcd.print("%");
}

String READ(){
  if(Node.available() > 0) {
    char data = Node.read();
    if(data == 'H') {
      String x = Node.readStringUntil('_');
      return x;
    }
    
    if(data == 'T') {
      String x = Node.readStringUntil('_');
      return x;
    }
  }
  return String(-1);
}


void latchData(float data, int row){
  if(data >= 0 && data < 10) {lcd.setCursor(9, row); lcd.print(" 0");
  lcd.setCursor(11, row); lcd.print(data);}

  else if(data >= 10 && data < 100) {lcd.setCursor(19, row); lcd.print(" ");
  lcd.setCursor(10, row); lcd.print(data);}

  else if(data >= 100) lcd.setCursor(9, row);
  else{};
}


void loop() {
  // put your main code here, to run repeatedly:
  float a;
  Node.print('h');
  a = READ().toFloat();
  if(a != -1){
    latchData(a, 0);
  }delay(400);
  
  Node.print('t');
  a = READ().toFloat();
  if(a != -1){
    latchData(a, 1);
  }delay(400);
}
