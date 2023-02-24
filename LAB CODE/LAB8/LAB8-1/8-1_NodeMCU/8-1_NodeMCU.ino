#include <SoftwareSerial.h>
SoftwareSerial Node(D2, D3);
void setup() {
  // put your setup code here, to run once:
  Node.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Node.print("&");
  Node.print(map(analogRead(A0), 10, 1023, 0, 255));
  Node.print("_");
  delay(10);
}
