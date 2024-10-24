#include<WiFi.h>
#include "ESP32Firebase.h"
#define FIREBASE_HOST "iot-462-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"
#define WIFI_SSID "Nothing Phone (2a) 5G"
#define WIFI_PASS "9705991317"
FirebaseData firebasedata;

float val = 0.0;
String tag = "IOT/462/TEST/VALUE";

void setup() {
  Serial.begin(115200);
  wifiinit();
  firebaseinit();

}

void loop() {
  firebasewrite();
  Serial.println(val);

  val = val + 1.5;
  if(val>20.0) val = 0.0;
  delay(1000);
}
void wifiinit(){
   WiFi.begin(WIFI_SSID,WIFI_PASS);
   Serial.print("Connecting to wi-fi");
   while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      delay(300);
    }
    Serial.println();
    Serial.println("Connected with ip: ");
    Serial.println(WiFi.localIP());
    Serial.println();
    
}
void firebaseinit(){
   Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
   Firebase.reconnectWiFi(true);
  }
void firebasewrite(){
  Firebase.setFloat(firebasedata,tag,val);
  }
