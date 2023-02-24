#include <SoftwareSerial.h>
SoftwareSerial ar(9, 10);
void setup() {
  // put your setup code here, to run once:
  ar.begin(9600);
  Serial.begin(9600);
}

String READ(){
  String a;
  while(ar.available() > 0) {
    if(ar.read() == '&') {
      String x = ar.readStringUntil('_');
      return x;
    }
  }
  return String(-1);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = READ().toInt();
  if(a != -1) {
    analogWrite(6, a);
    Serial.println(a);
  }
}
