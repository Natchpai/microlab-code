
#include <ESP8266WiFi.h>
// #include <time.h>
#include <WiFiUdp.h>

const char* ssid = "";                                //ใส่ชื่อ SSID Wifi
const char* password = "";                     //ใส่รหัสผ่าน

int timezone = 7 * 3600;                    //ตั้งค่า TimeZone ตามเวลาประเทศไทย
int dst = 0;                                //กำหนดค่า Date Swing Time
char buff1[20], buff2[20];

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);                                        //เชื่อมต่อ Wifi
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
     Serial.print(",");
     delay(1000);
   }
    configTime(timezone, dst, "pool.ntp.org", "time.nist.gov");     //ดึงเวลาจาก Server
    Serial.println("\nWaiting for time");
    while (!time(nullptr)) {
      Serial.print(".");
      delay(1000);
    }
    Serial.println();

}

void loop() {  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  
  sprintf(buff1,"%02d:%02d:%02d",p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);             // แปลงเวลาป็น String เก็บไว้ที่ buff1
  sprintf(buff2,"%02d/%02d/%02d",p_tm->tm_mday, p_tm->tm_mon+1, p_tm->tm_year+1900);      // แปลงวันที่เป็น String เก็บไว้ที่ buff2
  
  Serial.print(buff1); Serial.print(" ");
  Serial.print(buff2); Serial.print(" ");
  Serial.println();
  delay(1000);
}