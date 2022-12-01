float resultVolt;
unsigned int getValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

float convertInt2Volt(unsigned int value, unsigned int MaxValue, unsigned int MaxVolt) {
  return (float(value) / float(MaxValue) * float(MaxVolt));
}

// float con2(int *value, int volt) {
//   *value = *value * volt;
// }

unsigned int loadValueAnalog(uint8_t targetPin,  unsigned int from_min, unsigned int from_Max, unsigned int to_min, unsigned int to_Max) 
{  
  return map(analogRead(targetPin), from_min, from_Max, to_min, to_Max);
}

void loop() {
  // put your main code here, to run repeatedly:
  getValue = loadValueAnalog(A0, 0, 1023, 0, 1023);
  resultVolt = convertInt2Volt(getValue, 1023, 5);
  Serial.print("Analog: " + String(getValue) + ", Voltage: ");
  Serial.println(String(resultVolt, 1) + " V.");
  delay(100);
}
