#define led1 10
#define led2 9
#define led3 8
#define led4 7
#define led5 6
#define led6 5

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  Serial.begin(9600);  
}

int led_number = 1;
int slow = 1000;
void ActiveLED_0()
  {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }

void ActiveLED_1()
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }

void ActiveLED_2()
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }

void ActiveLED_3()
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }

void ActiveLED_4()
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }

 void ActiveLED_5()
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, LOW);
  }

 void ActiveLED_6()
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    digitalWrite(led6, HIGH);
  }

int i = 1; 
void loop() {
  // put your main code here, to run repeatedly:
  if(i == 1){
    ActiveLED_1();
    i++;
    }
   else if(i == 2){
    ActiveLED_2();
    i++;
    }
    else if(i == 3){
    ActiveLED_3();
    i++;
    }
    else if(i == 4){
    ActiveLED_4();
    i++;
    }
    else if(i == 5){
    ActiveLED_5();
    i++;
    }
    else if(i == 6){
    ActiveLED_6();
    i++;
    }
    else if(i == 7){
    ActiveLED_0();
    i = 1;
    }
  delay(1000);
}
