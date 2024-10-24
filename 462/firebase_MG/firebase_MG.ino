#include <WiFi.h>
 #include "FirebaseESP32.h"
 #define FIREBASE_HOST "https://iot-462-default-rtdb.firebaseio.com"
 #define FIREBASE_AUTH "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"
 #define WIFI_SSID "Nothing Phone (2a) 5G"
 #define WIFI_PASSWORD "9705991317"
 FirebaseData firebaseData;
 FirebaseAuth firebaseAuth;
 FirebaseConfig firebaseConfig;
 String sw;
 String tag="Firebase_ms/MS/sw";
 void setup(){
    pinMode(16,INPUT_PULLUP);
    Serial.begin(115200);
    WiFiInit();
    FirebaseInit(); 
 }
 void loop(){
  if(digitalRead(16) == HIGH){
    sw = "Open";
    }
    else{
      sw = "closed";
      }
  Serial.print(sw);
  Firebase.setString(firebaseData, tag, sw);
  delay(500);
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
 
 
