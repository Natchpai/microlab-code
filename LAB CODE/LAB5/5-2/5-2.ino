String inputCommand = "";
bool left = false;
bool right = false;

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
    unsigned int step = inputCommand.toInt();
    
    if(inputInRam == "LEFT") {
      activeMotor("left", step);
    }
    else if(inputInRam == "RIGHT") {
      activeMotor("right", step);
    }
    else return;

  }
  
}