#include <SPI.h>
#include <MFRC522.h>

#define SS 10
#define RST 9

MFRC522 rfid(SS, RST);
MFRC522::MIFARE_Key key;

char *UID[] = {"16:E2:70:A1", "70:53:5D:A8", "06:DA:FF:AC"};
uint8_t ArrayLen = 3;
String strID = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  SPI.begin();
  rfid.PCD_Init();
}

bool checkID() {
  for (int i=0; i<ArrayLen; i++){
    if(strID.indexOf(UID[i]) >= 0) return true;
  }
  return false;
}
  

void loop() {
  // put your main code here, to run repeatedly:
  if(!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  if(rfid.uid.uidByte > 0) {
    digitalWrite(7, HIGH); delay(100); digitalWrite(7, LOW);
  }


  for (byte i=0;i<4;i++) {
    strID += (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) + (i !=3 ? ":" : "");
  }
  strID.toUpperCase();

  Serial.print("ID: ");
  Serial.println(strID);
  if(checkID() == true) {Serial.println("Status : ALLOW ACCESS"); }
  else {Serial.println("Status : ACCESS DENIDE!");}

  strID = "";
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
