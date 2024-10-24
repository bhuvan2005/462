#include <WiFi.h>
#include <Wire.h>
#include <FirebaseESP32.h>
#include "MAX30105.h"
#include "heartRate.h"

#define wifi_ssid "Nothing Phone (2a) 5G"
#define wifi_pass "9705991317"
#define firebase_host "https://iot-462-default-rtdb.firebaseio.com"
#define firebase_auth "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"

MAX30105 particleSensor;
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData firebasedata;

const byte ratesize = 4;
byte rates[ratesize];
byte rateSpot = 0;
long lastBeat = 0;
float bpm;
int bavg;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(wifi_ssid,wifi_pass);
  Serial.print("Connecting to wifi.....");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
    
   Serial.println("Connected to Wi-Fi");
   Serial.print("IP Address: ");
   Serial.println(WiFi.localIP());

   Serial.println("Initializing...");

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST))
  {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

   
   config.host = firebase_host;
   config.signer.tokens.legacy_token = firebase_auth;

   Firebase.begin(&config, &auth);
   Firebase.reconnectWiFi(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    bpm = 60 / (delta / 1000.0);

    if (bpm < 255 && bpm > 20)
    {
      rates[rateSpot++] = (byte)bpm;
      rateSpot %= ratesize;
      bavg = 0;
      for (byte x = 0 ; x < ratesize ; x++)
        bavg += rates[x];
      bavg /= ratesize;
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(bpm);
  Serial.print(", Avg BPM=");
  Serial.print(bavg);

  if (irValue < 50000)
    Serial.print(" No finger?");
  Serial.println();
  if (Firebase.ready()) {
    Firebase.setFloat(firebasedata, "/MAX30105/irValue", irValue);
    Firebase.setFloat(firebasedata, "/MAX30105/BPM", bpm);
    Firebase.setFloat(firebasedata, "/MAX30105/Avg BPM", bavg);
    
  }
}
