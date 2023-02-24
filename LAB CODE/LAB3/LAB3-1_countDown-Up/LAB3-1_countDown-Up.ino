#define SW1 2
#define SW2 3
bool sw1State = 0;
bool sw2State = 0;
bool pullState = false;
// bool lastSw1State = 0;
// bool lastSw2State = 0;
int number = 0;
int c = 99;

void setup() {
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  Serial.begin(9600);
}

void countUp() {
  if(number < c && number >= 0) {
    number++;
  }
  else {
    number = 0;
  }
}

void countDown() {
  if(number <= c && number > 0) {
    number--;
  }
  else {
    number = c;
  }
}

void loop() {
  sw1State = digitalRead(SW1);
  if (sw1State == pullState) {
    delay(101);
    if (digitalRead(SW1) == pullState) {
      //condition
      countUp();
      Serial.println("Count Up: " + String(number));
      while (digitalRead(SW1) == pullState) {}
    }
  }

  sw2State = digitalRead(SW2);
  if (sw2State == pullState) {
    delay(50);
    if (digitalRead(SW2) == pullState) {
      //condition
      countDown();
      Serial.println("Count Down: " + String(number));
      while (digitalRead(SW2) == pullState) {}
    }
  }
}