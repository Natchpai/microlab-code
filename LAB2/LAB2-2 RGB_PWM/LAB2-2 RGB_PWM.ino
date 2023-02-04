#define redPin 11
#define bluePin 10
#define greenPin 9

uint8_t redValue = 0;
uint8_t greenValue = 0;
uint8_t blueValue = 0;

String getValue() {
  return Serial.readStringUntil('\n');
}

void resetPreviousDataSet() {
  redValue = 0;
  greenValue = 0;
  blueValue = 0;
}

void searchTarget(String data) {
  String IDKvalue; 
  for (int i = 0; i < data.length(); i++) {
    if (data[i] == 'R' || data[i] == 'r') {
      redValue = IDKvalue.toInt();
      IDKvalue = "";
      continue;
    }
    
    if (data[i] == 'G' || data[i] == 'g') {
      greenValue = IDKvalue.toInt();
      IDKvalue = "";
      continue;
    } 

    if (data[i] == 'B' || data[i] == 'b') {
      blueValue = IDKvalue.toInt();
      IDKvalue = "";
      continue;
    }

    IDKvalue += data[i];

  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    resetPreviousDataSet();

    searchTarget(getValue());

    Serial.println("---------------");
    Serial.print("R:" + String(redValue) + ", "); 
    Serial.print("G:" + String(greenValue) + ", "); 
    Serial.println("B:" + String(blueValue)); 
    
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
  }
}
