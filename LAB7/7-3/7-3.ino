
/* 

Information on a specific command
on                TURN ON
off               TURN OFF
play              PLAY LOOP
pause             PAUSE LOOP
reset             Setting Default.
loop {key}        Loop enable/disable
                  (key) on, off
show              Show/Display the LED's status.
hide              Hide the LED's status.
step set {key}    Set the stepping value of LEDs.
                  (key) left, right, one
mode              Show mode at the moment.
status            Show [All] setting at the moment.
time now          Show delay times at the moment.
time set {var}    Set delay times.
                  (var) time in ms.

*/

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

String inputCommand = "";
char Dict[] = {'0', '1', '2', '3', '4', '5', '6'};
int numberOfArray = 7;
int val = 0;
String systemName = "PEPPU@";
void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  // pinMode(reset, OUTPUT);
  Serial.begin(9600);

}


void ActiveLED(bool stat) {
  if(stat) {
    digitalWrite(led1, status_LED1);
    digitalWrite(led2, status_LED2);
    digitalWrite(led3, status_LED3);
    digitalWrite(led4, status_LED4);
    digitalWrite(led5, status_LED5);
    digitalWrite(led6, status_LED6);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }
}

void changeStatLED(int val) {
  switch(val) {
    case 0:
            status_LED1 = false;
            status_LED2 = false;
            status_LED3 = false;
            status_LED4 = false;
            status_LED5 = false;
            status_LED6 = false; break;
    case 1: status_LED1 = !status_LED1; break;
    case 2: status_LED2 = !status_LED2; break;
    case 3: status_LED3 = !status_LED3; break;
    case 4: status_LED4 = !status_LED4; break;
    case 5: status_LED5 = !status_LED5; break;
    case 6: status_LED6 = !status_LED6; break;
    default: break;
  }
}

bool checkDict(String text) {
  // check text in dictionary > Dict[index]
  for(int i = 0; i < numberOfArray; i++) {
    if(String(Dict[i]) == text) {
        return true;
    }
  }
  return false;
}


void MainActive() {
  if(Serial.available() > 0) {
    inputCommand = Serial.readStringUntil('\n');
    Serial.println(inputCommand);
    if(checkDict(inputCommand)) {
      val = inputCommand.toInt();
      changeStatLED(val);
      ActiveLED(1);
    }

    else {     
      Serial.print(systemName);
      Serial.print(" '");
      Serial.print(inputCommand);
      Serial.println("' is not recognized as an internal or external command or not in Range!");
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  MainActive();
}








