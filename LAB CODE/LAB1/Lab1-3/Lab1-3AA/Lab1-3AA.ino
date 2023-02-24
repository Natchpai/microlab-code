/* 

Information on a specific command
start;           Play
stop;            Pause
reset;           Setting Default
set step {var};  Set the stepping value of LEDs
                 (var) left, right, one
time now;        Show delay times
time set {var};  Set delay times
                 (var) time in ms.

*/

#define led1 10
#define led2 9
#define led3 8
#define led4 7
#define led5 6
#define led6 5
// #define reset 12

//STATUS LED
bool status_LED1 = false;
bool status_LED2 = false;
bool status_LED3 = false;
bool status_LED4 = false;
bool status_LED5 = false;
bool status_LED6 = false;

// STATUS THIS SYSTEM
bool POWER = true;  // Default Setting
bool left_shift = true; // Default Setting
bool right_shift = false;
bool one_step = false;

// SYSTEM SETTING
int Step = 0; // Default Setting *first Step
int stepInRam = 0;
unsigned int times = 1000; // Default Setting It can change in terminal
String systemName = "System$";
String lastText = ";";
String bookmark = "----------------------------------";

char *Dict[] = {"start", "stop", "set step left", "set step right", "set step one", "reset"};

String inputCommand = "";
String QC_input = "";

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
  Display();
  
}

void Display() {
  //  FIRST DISPLAY
  Serial.println("Information on a specific command");
  Serial.println("start;           Play");
  Serial.println("stop;            Pause");
  Serial.println("reset;           Setting Default");
  Serial.println("set step {var};  Set the stepping value of LEDs");
  Serial.println("                 (var) left, right, one");
  Serial.println("time now;        Show delay times");
  Serial.println("time set {var};  Set delay times");
  Serial.println("                 (var) time in ms.");
  Serial.println("");
  Serial.println("Enter any word to send message to your beloved!");

  while(true) {
    if(Serial.available() > 0) {
      break;
    }
  }
}

void printLED() {
  Serial.print("LED Status: ");
  if(status_LED1){
    Serial.print("1 ");
  }
  else{
    Serial.print("0 ");
  }

  if(status_LED2){
    Serial.print("1 ");
  }
  else{
    Serial.print("0 ");
  }

  if(status_LED3){
    Serial.print("1 ");
  }
  else{
    Serial.print("0 ");
  }

  if(status_LED4){
    Serial.print("1 ");
  }
  else{
    Serial.print("0 ");
  }

  if(status_LED5){
    Serial.print("1 ");
  }
  else{
    Serial.print("0 ");
  }

  if(status_LED6){
    Serial.println("1 ");
  }
  else{
    Serial.println("0 ");
  }
}

void ActiveLED() {
  digitalWrite(led1, status_LED1);
  digitalWrite(led2, status_LED2);
  digitalWrite(led3, status_LED3);
  digitalWrite(led4, status_LED4);
  digitalWrite(led5, status_LED5);
  digitalWrite(led6, status_LED6);
}

void restart() {
  Serial.print(systemName);
  Serial.println(" Restart...");
  for(int i = 1; i >= 0; i--) {
    Serial.print(systemName);
    Serial.println(" in " + String(i));
    delay(1000);
  }
  Step = 6;
  status_LED1 = false;
  status_LED2 = false;
  status_LED3 = false;
  status_LED4 = false;
  status_LED5 = false;
  status_LED6 = false;

  POWER = true;  
  left_shift = true; 
  right_shift = false;
  one_step = false;
  // digitalWrite(reset, HIGH);
}

void setMode() {
  // POWER ON
  if(QC_input == String(Dict[0])) {
    POWER = true;
    Step = stepInRam;
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println(" Set > Start...");
    stepInRam = 0;
  }
  // POWER OFF
  else if(QC_input == String(Dict[1])) {
    POWER = false;
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println(" Set > Stop...");
  }
  // Left Shift
   else if(QC_input == String(Dict[2])) {
    left_shift = true;
    right_shift = false;
    one_step= false;
    Step = 0;
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println(" Set > Step set 'Left Step'");
  }
  // Right Shift
   else if(QC_input == String(Dict[3])) {
    left_shift = false;
    right_shift = true;
    one_step= false;
    Step = 0;
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println(" Set > Step set 'Right Step'");
  }
  // One Step
   else if(QC_input == String(Dict[4])) {
    left_shift = false;
    right_shift = false;
    one_step= true;
    Step = 0;
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println(" Set > Step set 'One Step'");
  }
  // Reset
   else if(QC_input == String(Dict[5])) {
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println(" Set > Reset");
    restart();
  }
  else {}

}

String delLastIndex(String text) {
  // remove last index default 
  int lastIndex = text.length() - 1;
  text.remove(lastIndex);
  return text;
}

bool checkLastIndex(String text) {
  // check Last indext
  int lastIndex = text.length() - 1;
  if(String(text[lastIndex]) == lastText) {
    return true;
  }
  return false;
}

bool checkDict(String text) {
  // check text in dictionary > Dict[index]
  for(int i = 0; i < 6; i++) {
    if(String(Dict[i]) == text) {
        return true;
    }
  }
  return false;
}

bool checkInt(String text) {
  for(int i = 0; i <= text.length(); i++) {
    if(isDigit(text[i])) {
      return true;
    }
  }
  return false;
}

bool checkTimeSet(String text) {
  if(text.indexOf("time set ") == 0) {
    return true;
  }
  else if(text.indexOf("time now") == 0) {
    return true;
  }
  return false;
}

void timeSet(String text) {
  String textInRam = text;
  if(text == "time now") {
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println("Times is " + String(times) + "ms.");
  }
  textInRam.remove(9);
  if(textInRam == "time set ") {
    textInRam = "";
    text.remove(0, 9);
    times = text.toInt();
    Serial.println(bookmark);
    Serial.print(systemName);
    Serial.println("Time set at " + String(times) + " ms.");
  }
}

void changeStatLED(int Step, bool left, bool right, bool one) {
  if(left) {
    switch(Step) {
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
  }
  else if(right) {
    switch(Step) {
      case 0: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = false;
              status_LED4 = false;
              status_LED5 = false;
              status_LED6 = false;
      break;
      case 1: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = false;
              status_LED4 = false;
              status_LED5 = false;
              status_LED6 = true;
      break;
      case 2: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = false;
              status_LED4 = false;
              status_LED5 = true;
              status_LED6 = true;
      break;
      case 3: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = false;
              status_LED4 = true;
              status_LED5 = true;
              status_LED6 = true;
      break;
      case 4: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = true;
              status_LED4 = true;
              status_LED5 = true;
              status_LED6 = true;
      break;
      case 5: status_LED1 = false;
              status_LED2 = true;
              status_LED3 = true;
              status_LED4 = true;
              status_LED5 = true;
              status_LED6 = true;
      break;
      case 6: status_LED1 = true;
              status_LED2 = true;
              status_LED3 = true;
              status_LED4 = true;
              status_LED5 = true;
              status_LED6 = true;
      break;
    } 
  }
  else if(one) {
    switch(Step) {
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
      case 2: status_LED1 = false;
              status_LED2 = true;
              status_LED3 = false;
              status_LED4 = false;
              status_LED5 = false;
              status_LED6 = false;
      break;
      case 3: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = true;
              status_LED4 = false;
              status_LED5 = false;
              status_LED6 = false;
      break;
      case 4: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = false;
              status_LED4 = true;
              status_LED5 = false;
              status_LED6 = false;
      break;
      case 5: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = false;
              status_LED4 = false;
              status_LED5 = true;
              status_LED6 = false;
      break;
      case 6: status_LED1 = false;
              status_LED2 = false;
              status_LED3 = false;
              status_LED4 = false;
              status_LED5 = false;
              status_LED6 = true;
      break;

    }
  }
}

void ACTIVE_COMMAND() {
  if(POWER) {
    changeStatLED(Step, left_shift, right_shift, one_step);
  }
  else{
    // Onigiri While loop
    stepInRam = Step;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  for(Step; Step <= 6; Step++) {
    // Serial.print("(Clock) " + String(Step) + " ");
    
    if(Serial.available() > 0) {
      inputCommand = Serial.readStringUntil('\n');

      if(checkLastIndex(inputCommand)) {
        QC_input = delLastIndex(inputCommand);

        if(checkTimeSet(QC_input)) {
          timeSet(QC_input);
        }

        else if(checkDict(QC_input)) {
          // QC PASS
          setMode();
        }

        else {     
          Serial.println(bookmark);
          Serial.print(systemName);
          Serial.print(" '");
          Serial.print(QC_input);
          Serial.println("' is not recognized as an internal or external command.");
        }

      }
      else {
        Serial.println(bookmark);
        Serial.print(systemName);
        Serial.print(" Command error: expected '" + lastText);
        Serial.println("' before Command token");
      }
    }
    else {
      ACTIVE_COMMAND();
      ActiveLED();
      printLED();
    }
    delay(times);
  }
  // Reset Step(clock)
  Step = 0;

}







