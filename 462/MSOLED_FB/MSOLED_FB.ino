#include <WiFi.h>
#include <Wire.h>
#include "SSD1306.h"
#include "FirebaseESP32.h"

#define FIREBASE_HOST "https://iot-462-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"
#define WIFI_SSID "Nothing Phone(2a)5G"
#define WIFI_PASSWORD "9705991317"

FirebaseData firebaseData;
FirebaseAuth firebaseAuth;
FirebaseConfig firebaseConfig;
SSD1306 display(0x3c, 21, 22);

const char* tag = "MSOLED_firebase/mystring";
char mystring[5];

void setup() {
    Serial.begin(115200);
    pinMode(16, INPUT_PULLUP);
    WiFiInit();
    FirebaseInit();
    oledInit();
}

void loop() {
     Firebase.setString(firebaseData, tag, mystring);
    if (digitalRead(16) == HIGH)
        strcpy(mystring,"OPEN");
    else
        strcpy(mystring,"CLOSE");
    Serial.println(mystring);
    
    OLEDUpdate();
    delay(500);
}

void oledInit() {
    display.init();
    display.setFont(ArialMT_Plain_24);
}

void WiFiInit() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
}

void FirebaseInit() {
    firebaseConfig.host = FIREBASE_HOST;
    firebaseConfig.signer.tokens.legacy_token = FIREBASE_AUTH;
    Firebase.begin(&firebaseConfig, &firebaseAuth);
    Firebase.reconnectWiFi(true);
}

void OLEDUpdate() {
    display.clear();
    display.drawString(0, 0, mystring);
    display.display();
}
