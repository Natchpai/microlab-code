
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
bool disLED = true;

// Default Setting
bool POWER = true;
bool left_shift = false; 
bool right_shift = false;
bool one_step = true;
bool Loop = false;
bool pause = false;

// SYSTEM SETTING
int val = 0; // Default Setting *first Step
unsigned int times = 1000; // Default Setting It can change in terminal
String systemName = "System$";
String lastText = ";";


// FIXABLE!! DO NOT SWITCH INDEX PLEASE
char *Dict[] = {"on", "off", "step set left", "step set right", "step set one", "reset", "mode", "show", "hide", "loop off", "loop on", "pause", "play", "status"};
int numberOfArray = 14;  // When edit *Dict[] please change numberOfArray("array length"). thank you❤️. 
String inputCommand = "";

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

void printLED(bool stat) {
  if(stat) {
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

void restart() {
  Serial.print(systemName);
  Serial.println(" Restart...");
  for(int i = 1; i >= 0; i--) {
    Serial.print(systemName);
    Serial.println(" in " + String(i));
    delay(1000);
  }
  status_LED1 = false;
  status_LED2 = false;
  status_LED3 = false;
  status_LED4 = false;
  status_LED5 = false;
  status_LED6 = false;
  disLED = true;
  times = 1000;
  POWER = true;
  left_shift = false; 
  right_shift = false;
  one_step = true;
  Loop = false;
  pause = false;
  val = 0;
  // digitalWrite(reset, HIGH);
}

void setMode(String QC_input) {
  // POWER ON
  if(QC_input == String(Dict[0])) {
    POWER = true;
    val = -1;
    Serial.print(systemName);
    Serial.println(" System enable...");
  }
  // POWER OFF
  else if(QC_input == String(Dict[1])) {
    POWER = false;
    val = -1;
    Serial.print(systemName);
    Serial.println(" System disable...");
  }
  // Left Shift
  else if(QC_input == String(Dict[2])) {
    left_shift = true;
    right_shift = false;
    one_step= false;
    Serial.print(systemName);
    Serial.println(" Set > Step set 'Left Step'");
  }
  // Right Shift
  else if(QC_input == String(Dict[3])) {
    left_shift = false;
    right_shift = true;
    one_step= false;

    Serial.print(systemName);
    Serial.println(" Set > Step set 'Right Step'");
  }
  // One Step
  else if(QC_input == String(Dict[4])) {
    left_shift = false;
    right_shift = false;
    one_step= true;

    Serial.print(systemName);
    Serial.println(" Set > Step set 'One Step'");
  }
  // Reset
  else if(QC_input == String(Dict[5])) {

    Serial.print(systemName);
    Serial.println(" Set > Reset");
    restart();
  }
  // Show mode
  else if(QC_input == String(Dict[6])) {
    Serial.print(systemName);
    Serial.println(" Show Current Mode: LED " + String(Mode()));
  }
  // Show LED's status
  else if(QC_input == String(Dict[7])) {
    Serial.print(systemName);
    disLED = true;
    Serial.println(" Set > disLED = true;");

    Serial.print(systemName);
    Serial.println(" Show Status LEDs... ");
  }
  // hide LED's status
  else if(QC_input == String(Dict[8])) {
    Serial.print(systemName);
    disLED = false;
    Serial.println(" Set > disLED = false;");

    Serial.print(systemName);
    Serial.println(" Hide Status LEDs... ");
  }
  // Set loop Disable
  else if(QC_input == String(Dict[9])) {
    Serial.print(systemName);
    Loop = false;
    Serial.println(" Set > Loop Disable");
  }
  // Set loop Enable
  else if(QC_input == String(Dict[10])) {
    Serial.print(systemName);
    Loop = true;
    Serial.println(" Set > Loop Enable");
    Serial.print(systemName);
    Serial.println(" At " + String(times) + " ms.");
  }
  // Set pause
  else if(QC_input == String(Dict[11])) {
    Serial.print(systemName);
    Loop = false;
    pause = true;
    Serial.println(" Set > System pause!");
  }
  // Set play
  else if(QC_input == String(Dict[12])) {
    Serial.print(systemName);
    Loop = true;
    pause = false;
    Serial.println(" Set > System play!");
    Serial.print(systemName);
    Serial.println(" !Status Active, Step " + String(Mode()) + ", time " + String(times) + " ms.");
  }
  // Show [All] setting/status
  else if(QC_input == String(Dict[13])) {
    Serial.print(systemName);
    Serial.println(" Show [All] Status and Setting");
    // Serial.print(systemName);
    Serial.print(String(showPOWER()) + ", " + String(showLeftShift()));
    Serial.print(String(showRightShift()) + ", " + String(showOneStep()));
    Serial.println(String(showLoop()) + ", "+ String(showPause()));
    Serial.print(String(showTime()) + "\n");
  }

  else {}

}

String showPOWER() {
  if(POWER) {
    return "'POWER' : true ";
  }
    return "'POWER' : false ";
}

String showLeftShift() {
  if(left_shift) {
    return "'left_shift' : true ";
  }
    return "'left_shift' : false ";
}

String showRightShift() {
  if(right_shift) {
    return "'right_shift' : true ";
  }
    return "'right_shift' : false ";
}

String showOneStep() {
  if(one_step) {
    return "'one_step' : true ";
  }
    return "'one_step' : false ";
}

String showLoop() {
  if(Loop) {
    return "'Loop' : true ";
  }
    return "'Loop' : false ";
}

String showPause() {
  if(pause) {
    return "'pause' : true ";
  }
    return "'pause' : false ";
}

String showTime() {
    return "'times' : " + String(times) + " ms.";
}

String Mode() {
  if(left_shift) {return String(val) + ", " + "Left Step Shift";}
  else if (right_shift) {return String(val) + ", " + "Right Step Shift";}
  else if (one_step) {return String(val) + ", " + "One Step";}
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
  for(int i = 0; i < numberOfArray; i++) {
    if(String(Dict[i]) == text) {
        return true;
    }
  }
  return false;
}

bool checkInt_inString(String text) {
  for(int i = 0; i <= text.length(); i++) {
    if(isDigit(text[i])) {
      return true;
    }
  }
  return false;
}

bool checkAlpha_inInt(String text) {
  for(int i = 0; i <= text.length(); i++) {
    if(isAlpha(text[i])) {
      return false;
    }
  }
  return true;
}

bool range(int val, int min, int Max) {
  // min <= X <= Max
  return ((min <= val) && (val <= Max));
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

    Serial.print(systemName);
    Serial.println(" Time is " + String(times) + " ms.");
  }
  textInRam.remove(9);
  if(textInRam == "time set ") {
    textInRam = "";
    text.remove(0, 9);
    times = text.toInt();

    Serial.print(systemName);
    Serial.println(" Time set " + String(times) + " ms.");
  }
}

bool checkDuplicateOrder(String text) {
  // ขี้เกียจทำ
}

// FIXABLE!! DO NOT SWITCH PLEASE
void editVal() {
  if(Loop) {
    if(val != 0){
        val = val - 1;
      }
      else {val = 6;}
  }
}

void changeStatLED(int Step, bool left, bool right, bool one, bool status) {
  if(status) {
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
  else {
    status_LED1 = false;
    status_LED2 = false;
    status_LED3 = false;
    status_LED4 = false;
    status_LED5 = false;
    status_LED6 = false;
  }
}


void MainActive() {
  if(Serial.available() > 0) {
    inputCommand = Serial.readStringUntil('\n');
    
    if(checkDict(inputCommand)) {
      editVal(); // FIXABLE!! DO NOT SWITCH PLEASE
      setMode(inputCommand);
    }

    else if(checkTimeSet(inputCommand)) {
      editVal(); // FIXABLE!! DO NOT SWITCH PLEASE
      timeSet(inputCommand);
    } 

    else if(checkAlpha_inInt(inputCommand)) {
      val = inputCommand.toInt();
      if(range(val, 0, 6)) {
        Serial.print(systemName);
        Serial.println(" Change LED: " + String(Mode()));
        changeStatLED(val, left_shift, right_shift, one_step, POWER);
        ActiveLED(1);
      }  
      else {
        Serial.print(systemName);
        Serial.print(" WARNING!! '" + String(val));
        Serial.println("' is not in Range!");
      }
    }

    else {     
      Serial.print(systemName);
      Serial.print(" '");
      Serial.print(inputCommand);
      Serial.println("' is not recognized as an internal or external command.");
    }
  }
  else {
    changeStatLED(val, left_shift, right_shift, one_step, POWER);
    ActiveLED(1);
    printLED(disLED);
  }
  delay(times);
}

void loop() {
// put your main code here, to run repeatedly:

  if(Loop) {
    // FIXABLE!! DO NOT SWITCH PLEASE
    val = val + 1;
    if(val > 6) { val = 0; }
    MainActive();
    // FIXABLE!! DO NOT SWITCH PLEASE
  }
  else {
    MainActive();
  }
}








