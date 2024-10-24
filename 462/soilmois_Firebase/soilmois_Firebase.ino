#include <WiFi.h>
#include<Wire.h>
#include "SSD1306.h"
 #include "FirebaseESP32.h"
 #define FIREBASE_HOST "https://iot-462-default-rtdb.firebaseio.com"
 #define FIREBASE_AUTH "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"
 #define WIFI_SSID "Nothing Phone(2a)5G"
 #define WIFI_PASSWORD "9705991317"
 FirebaseData firebaseData;
 FirebaseAuth firebaseAuth;
 FirebaseConfig firebaseConfig;
 SSD1306 display(0x3c,21,22);
String mystring;
 int sm;
 String tag="soilmoistureOLED_firebase/sm";
 void setup(){
    Serial.begin(115200);
    WiFiInit();
    FirebaseInit(); 
    oledinit();
 }
 void loop(){
  FirebaseWrite();
  sm = 4095 - analogRead(34);
  Serial.println(sm);
  OLEDUpdate();
  delay(500);
 }
 void oledinit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
  }

  void WiFiInit() {
  WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  Serial.print("connecting to Wi-Fi");
  while(WiFi.status() !=WL_CONNECTED) {
    Serial.print(".");
    delay(300); 
 }
  Serial.println();
  Serial.print("connected with ip:");
  Serial.println(WiFi.localIP());
  Serial.println();
 }
 void FirebaseInit() {
  firebaseConfig.host=FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token=FIREBASE_AUTH;
  Firebase.begin(&firebaseConfig,&firebaseAuth);
  Firebase.reconnectWiFi(true);
 }
 void FirebaseWrite(){
  Firebase.setFloat(firebaseData, tag, sm);
 }
 void OLEDUpdate(){
    display.clear();
    mystring = sm;
    display.drawString(0,0,mystring);
    display.display();
  }
  



  
