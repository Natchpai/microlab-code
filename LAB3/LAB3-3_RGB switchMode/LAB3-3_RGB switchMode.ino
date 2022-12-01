#define SW1 2
#define SW2 3
#define RED 9
#define GREEN 10
#define BLUE 11

unsigned long previousPress = 0;
unsigned long previousPress2 = 0;
uint8_t Mode = 1;
bool dataReceived = true;
bool sw1State = 0;
bool sw2State = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  attachInterrupt(0, button1, CHANGE);
  attachInterrupt(1, button2, CHANGE);

  // Setup Default
  Serial.println("Get information from the [Value]");
  Serial.println("Select Mode: Red");
}

void button1(){
  sw1State = 1;
}

void button2(){
  sw2State = 1;
}

void selectMode() {
  if (((millis() - previousPress) > 200) && sw1State) {
    previousPress = millis();
    if (digitalRead(SW1) == LOW) {
      if(Mode < 3 && Mode >= 1) {
        Mode++;
      }
      else {
        Mode = 1;
      }
      
      if (Mode == 1) {Serial.println("Select Mode: Red");}
      else if (Mode == 2) {Serial.println("Select Mode: Green");}
      else if (Mode == 3) {Serial.println("Select Mode: Blue");}
      sw1State = 0;
    }
  }
  if (((millis() - previousPress2) > 200 ) && sw2State) {
    previousPress2 = millis();
    if(digitalRead(SW2) == LOW) {
      
      dataReceived = !dataReceived;
      if (dataReceived == false) {
        Serial.println("Not receiving information from the [Value]");
        digitalWrite(13, LOW);
      }
      else {
        Serial.println("Get information from the [Value]");
        digitalWrite(13, HIGH);
      }
      sw2State = 0;
    }
  }
}

uint8_t readAnalog() {
  return map(analogRead(A0), 0, 1023, 0, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Mode 1 is Red
  selectMode();
  if (Mode == 1 && dataReceived) {
    analogWrite(RED, readAnalog());
  }
  // Mode 2 is Green
  if (Mode == 2 && dataReceived) {
    analogWrite(GREEN, readAnalog());
  }
  // Mode 3 is Blue
  if (Mode == 3 && dataReceived) {
    analogWrite(BLUE, readAnalog());
  }
}
