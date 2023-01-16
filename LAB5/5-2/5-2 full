String inputCommand = "";
bool left = false;
bool right = false;

int Steps[4][4] = {{1,0,0,0},
                  {0,1,0,0},
                  {0,0,1,0},
                  {0,0,0,1}};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}


void activeMotor(String direct, unsigned int step) {
  Serial.print(direct); Serial.println(step);

}


void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available() > 0) {
    inputCommand = Serial.readStringUntil('\n');
  inputCommand.toUpperCase();
    String inputInRam = inputCommand;
    inputInRam.remove(inputCommand.indexOf("T")+1);
    inputCommand.remove(0, inputCommand.indexOf("T")+1);
    unsigned int Step = inputCommand.toInt();
    
    if(inputInRam == "LEFT") {
      activeMotor("left", Step);
    }
    else if(inputInRam == "RIGHT") {
      activeMotor("right", Step);
    }
    else return;

  }
  
}

void activeMotor(String dir,int Step){
  if(dir == "left"){
    for(int i=0 ;i<Step ;i++){
      digitalWrite(2,Steps[i][0]);
      digitalWrite(3,Steps[i][1]);
      digitalWrite(4,Steps[i][2]);
      digitalWrite(5,Steps[i][3]);
      delay(10);
    }
  }
    if(dir == "right"){
      for(int i=0 ;i<Step ;i++){
      digitalWrite(2,Steps[i][3]);
      digitalWrite(3,Steps[i][2]);
      digitalWrite(4,Steps[i][1]);
      digitalWrite(5,Steps[i][0]);
      delay(10);
    }
}
}
  
