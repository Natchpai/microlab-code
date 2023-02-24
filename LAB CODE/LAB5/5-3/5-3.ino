#include <Servo.h>
Servo servo;
bool state = 0;

void stateSW() {
  state = !state;
}

void setup() {
  // put your setup code here, to run once:
  servo.attach(4);
  attachInterrupt(0, stateSW, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (state == 0) {
    servo.write(map(analogRead(A0), 0, 1023, 0, 180));
  }
}
