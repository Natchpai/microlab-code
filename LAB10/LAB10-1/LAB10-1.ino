#include <TridentTD_LineNotify.h>

#define SSID        "NatchPai"
#define PASSWORD    "powerpay4"
#define LINE_TOKEN  "aHzRDx0i15AkRVIfDGKt7h5DFn9T4NIY5ND5zF485u2"

#define SW1 D1
bool sw1State;
unsigned long previousPress;
unsigned long previous;
uint16_t dataReceived;
void setup() {
  Serial.begin(9600); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n",  SSID);
  while(WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400); }
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());  

  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);

  attachInterrupt(digitalPinToInterrupt(SW1), button1, FALLING);
  pinMode(SW1, INPUT);
}

ICACHE_RAM_ATTR void button1(){
  sw1State = 1;
}

void loop() {
  if (((millis() - previousPress) > 300 ) && sw1State) {
    previousPress = millis();
    if(digitalRead(SW1) == LOW) {
      LINE.notify("ตกกะปิ");
      sw1State = 0;
    }
  }

  dataReceived = analogRead(A0);
  Serial.println(dataReceived);
  if ((dataReceived <= 200) && (millis() - previous) > 5000 ) {
    previous = millis();
    LINE.notify("มันไม่สว่างสดใสเลย");
  }
}