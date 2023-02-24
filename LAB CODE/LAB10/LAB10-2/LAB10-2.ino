#include <TridentTD_LineNotify.h>

#define SSID        "NatchPai"
#define PASSWORD    "powerpay4"
#define LINE_TOKEN  "aHzRDx0i15AkRVIfDGKt7h5DFn9T4NIY5ND5zF485u2"

#include "DHT.h"
DHT dht(D4, DHT22);

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
  dht.begin();
}

ICACHE_RAM_ATTR void button1(){
  sw1State = 1;
}

void sendData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  LINE.notify("อุณหภูมิ " + String(t) + " องศา");
  LINE.notify("ความชื้นฯ " + String(h) + " เปอร์เซ็นต์");
}

void loop() {
  if (((millis() - previousPress) > 300 ) && sw1State) {
    previousPress = millis();
    if(digitalRead(SW1) == LOW) {
      sendData();
      sw1State = 0;
    }
  }

  if ((millis() - previous) >= 10000 ) {
    previous = millis();
    sendData();
  }
}