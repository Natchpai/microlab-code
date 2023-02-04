
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i=0; i<=27; i++) {
  lcd.setCursor(15, 0);
  lcd.print("NATCHANON THUENTHAM");
  lcd.setCursor(15, 1);
  lcd.print("6303102120128");
  lcd.scrollDisplayLeft();
  delay(300);}
  
  for (int i=0; i<=27; i++) {
  lcd.setCursor(15, 0);
  lcd.print("KRITIMA PHATSAI");
  lcd.setCursor(15, 1);
  lcd.print("6303102110254");
  lcd.scrollDisplayLeft();
  delay(300);}
}
