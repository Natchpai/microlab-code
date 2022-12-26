#define SW1 10
#define SW2 11
unsigned long currentTime;
unsigned long previousTime;
unsigned long previousPress = 0;
unsigned long previousPress2 = 0;
uint8_t second = 0;
uint8_t minute = 0;
uint8_t hour = 0;

bool sw1State = 0;
bool sw2State = 0;
bool pullState = false;
int number = 0;
int c = 99;
bool detectBug = 0;

uint8_t num[] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};  // Anode
// uint8_t num[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};  // Cathod
uint8_t digit[] = {0xFE, 0xFD};

void setup() {
  // put your setup code here, to run once:
  DDRD = 0xFF;
  DDRB = 0x03;
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
}
 
void dLatch(uint8_t data) {
  PORTD = num[data/10];
  PORTB = digit[0];
  delay(5);
  PORTB = 0xFF;
  PORTD = 0x00;

  PORTD = num[data%10];
  PORTB = digit[1];
  delay(5);
  PORTB = 0xFF;
  PORTD = 0x00;
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

void generateTime() {
  currentTime = millis();
  if(currentTime - previousTime >= 1000) {
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

void detectSwitchs() {
  sw1State = digitalRead(SW1);
  if (((millis() - previousPress) > 200) && !sw1State) {
    previousPress = millis();
    if (digitalRead(SW1) == pullState) {
      countUp();
    }
    while (digitalRead(SW1) == pullState) {
      dLatch(number);
    }
  }

  sw1State = digitalRead(SW2);
  if (((millis() - previousPress) > 200) && !sw2State) {
    previousPress = millis();
    if (digitalRead(SW2) == pullState) {
      countDown();
    }
    while (digitalRead(SW2) == pullState) {
      dLatch(number);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  detectSwitchs();
  dLatch(number);
}
