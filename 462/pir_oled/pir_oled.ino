#include <WiFi.h>
#include "SSD1306.h"
#include "FirebaseESP32.h"
#define FIREBASE_HOST "https://iot-462-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"
#define WIFI_SSD "Nothing Phone (2a) 5G"
#define WIFI_PASSWORD "9705991317"
FirebaseData firebaseData;
FirebaseAuth firebaseAuth;
FirebaseConfig firebaseConfig;
SSD1306 display(0x3c,21,22);
const int pir = 33;
int sw;
String mystring;
String tag = "firebase_pir/pir/motion";
void setup() {
  WiFi.begin(WIFI_SSD,WIFI_PASSWORD);
  firebaseinit();
  oledinit();
  pinMode(pir,INPUT);
  Serial.begin(9600);
}

void loop() {
   sw = digitalRead(pir);
  if(sw == 1){
      mystring = "object detected";
    }
   else{
     mystring = "Not detected";
   }
   Serial.println(mystring);
  OLEDUpdate();
  Firebase.setString(firebaseData,tag,mystring);
  delay(500);
}
void oledinit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
  }
 void firebaseinit() {
  firebaseConfig.host=FIREBASE_HOST;
  firebaseConfig.signer.tokens.legacy_token=FIREBASE_AUTH;
  Firebase.begin(&firebaseConfig,&firebaseAuth);
  Firebase.reconnectWiFi(true);
 }
void OLEDUpdate(){
    display.clear();
    display.drawString(0,0,mystring);
    display.display();
  }
