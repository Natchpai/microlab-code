#define SW1 D2
#define SW2 D3
#define led1 D1
#define led2 D4
#define led3 D5
#define led4 D6
#define led5 D7
#define led6 D8

bool status_LED1 = false;
bool status_LED2 = false;
bool status_LED3 = false;
bool status_LED4 = false;
bool status_LED5 = false;
bool status_LED6 = false;

// Mode setting
int c = 6;
int number = 0;
// Button Setting
bool sw1State = 0;
bool sw2State = 0;
int buttonDeBounce = 230;
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
    number = c;
  }
  Serial.println("Count Up: " + String(number));
}

void countDown() {
  if(number <= c && number > 0) {
    number--;
  }
  else {
    number = 0;
  }
  Serial.println("Count Down: " + String(number));
}

ICACHE_RAM_ATTR void button1() {
  sw1State = 1;  
}

ICACHE_RAM_ATTR void button2() {
  sw2State = 1;
}

void setup() {
  Serial.begin(9600);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(SW1), button1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SW2), button2, CHANGE);
}


void loop() {
  // put your main code here, to run repeatedly:
  // currentTimes = millis();
  // if (currentTimes - previousTimes > 2000) {
  //   digitalWrite(13, !digitalRead(13));
  //   previousTimes = currentTimes;
  // }
  switch(number) {
    case 0: status_LED1 = false;
            status_LED2 = false;
            status_LED3 = false;
            status_LED4 = false;
            status_LED5 = false;
            status_LED6 = false;
    break;
    case 1: status_LED1 = true;
            status_LED2 = false;
            status_LED3 = false;
            status_LED4 = false;
            status_LED5 = false;
            status_LED6 = false;
    break;
    case 2: status_LED1 = true;
            status_LED2 = true;
            status_LED3 = false;
            status_LED4 = false;
            status_LED5 = false;
            status_LED6 = false;
    break;
    case 3: status_LED1 = true;
            status_LED2 = true;
            status_LED3 = true;
            status_LED4 = false;
            status_LED5 = false;
            status_LED6 = false;
    break;
    case 4: status_LED1 = true;
            status_LED2 = true;
            status_LED3 = true;
            status_LED4 = true;
            status_LED5 = false;
            status_LED6 = false;
    break;
    case 5: status_LED1 = true;
            status_LED2 = true;
            status_LED3 = true;
            status_LED4 = true;
            status_LED5 = true;
            status_LED6 = false;
    break;
    case 6: status_LED1 = true;
            status_LED2 = true;
            status_LED3 = true;
            status_LED4 = true;
            status_LED5 = true;
            status_LED6 = true;
    break;
  }

  digitalWrite(led1, status_LED1);
  digitalWrite(led2, status_LED2);
  digitalWrite(led3, status_LED3);
  digitalWrite(led4, status_LED4);
  digitalWrite(led5, status_LED5);
  digitalWrite(led6, status_LED6);

  if (((millis() - previousPress) > buttonDeBounce) && sw1State) {
    previousPress = millis();
    if (digitalRead(D2) == LOW) {
      countUp();
      sw1State = 0;
    }
  }
  if (((millis() - previousPress2) > buttonDeBounce) && sw2State) {
    previousPress2 = millis();
    if (digitalRead(D3) == LOW) {
      countDown();
      sw2State = 0;
    }
  }
}
