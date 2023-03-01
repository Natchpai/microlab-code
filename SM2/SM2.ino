#define ch1 12
#define ch2 14                                     
#define ch3 27
#define ch4 26

#define BLYNK_TEMPLATE_ID "TMPLJrbeaKF0"
#define BLYNK_TEMPLATE_NAME "SHome"
#define BLYNK_AUTH_TOKEN "tqAb_SEB9XyxY8Q0ivvLg_6TCXRJA8BF"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "tqAb_SEB9XyxY8Q0ivvLg_6TCXRJA8BF";
char ssid[] = "NatchPai";
char pass[] = "powerpay4";


BLYNK_WRITE(V0)
{

  int value = param.asInt();
  Serial.print("ch1 : ");
  Serial.println(value);
  if(value == 1) {digitalWrite(ch1, 0);}
  else if(value == 0){digitalWrite(ch1, 1);}
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  Serial.print("ch2 : ");
  Serial.println(value);
  if(value == 1) {digitalWrite(ch2, 0);}
  else if(value == 0){digitalWrite(ch2, 1);}
}

BLYNK_WRITE(V2)
{
  int value = param.asInt();
  Serial.print("ch3 : ");
  Serial.println(value);
  if(value == 1) {digitalWrite(ch3, 0);}
  else if(value == 0){digitalWrite(ch3, 1);}
}

BLYNK_WRITE(V3)
{
  int value = param.asInt();
  Serial.print("ch4 : ");
  Serial.println(value);
  if(value == 1) {digitalWrite(ch4, 0);}
  else if(value == 0){digitalWrite(ch4, 1);}
}


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(ch1, OUTPUT);
  pinMode(ch2, OUTPUT);
  pinMode(ch3, OUTPUT);
  pinMode(ch4, OUTPUT);
  digitalWrite(ch1, 1); 
  digitalWrite(ch2, 1);
  digitalWrite(ch3, 1);
  digitalWrite(ch4, 1);
}


void loop()
{
  Blynk.run();
}
