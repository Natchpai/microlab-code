#define SW1 2
#define SW2 3
// Mode setting
int c = 99;
int number = 0;
// Button Setting
bool sw1State = 0;
bool sw2State = 0;
int buttonDeBounce = 200;
// times setting
unsigned long previousPress = 0;
unsigned long previousPress2 = 0;
unsigned long previousTimes = 0;
unsigned long currentTimes = 0;

void countUp() {
  if(number < c && number >= 0) {
    number++;
  }
  else {
    number = 0;
  }
  Serial.println("Count Up: " + String(number));
}

void countDown() {
  if(number <= c && number > 0) {
    number--;
  }
  else {
    number = c;
  }
  Serial.println("Count Down: " + String(number));
}

void button1() {
  sw1State = 1;  
}

void button2() {
  sw2State = 1;
}

void setup() {
  Serial.begin(9600);
  pinMode(SW1, INPUT);
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  attachInterrupt(0, button1, CHANGE);
  attachInterrupt(1, button2, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTimes = millis();
  if (currentTimes - previousTimes > 2000) {
    digitalWrite(13, !digitalRead(13));
    previousTimes = currentTimes;
  }

  if (((millis() - previousPress) > buttonDeBounce) && sw1State) {
    previousPress = millis();
    if (digitalRead(2) == LOW) {
      countUp();
      sw1State = 0;
    }
  }
  if (((millis() - previousPress2) > buttonDeBounce) && sw2State) {
    previousPress2 = millis();
    if (digitalRead(3) == LOW) {
      countDown();
      sw2State = 0;
    }
  }
}
