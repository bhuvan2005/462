#include<WiFi.h>
#include"FirebaseESP32.h"
#include<Wire.h>
#include<MPU6050.h>

#define firebase_host ""
#define firebase_auth ""
#define ssid ""
#define pass ""

FirebaseData firebasedata;
FirebaseAuth firebaseauth;
FirebaseConfig firebaseconfig;

String tag = "MPU6050";

MPU6050 mpu;

void setup() {
  WiFi.begin(ssid,pass);
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
}
void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print("Accelerometer: ");
    Serial.print("X: "); Serial.print(ax);
    Serial.print(" Y: "); Serial.print(ay);
    Serial.print(" Z: "); Serial.println(az);
    Serial.print("Gyroscope: ");
    Serial.print("X: "); Serial.print(gx);
    Serial.print(" Y: "); Serial.print(gy);
    Serial.print(" Z: "); Serial.println(gz);

    delay(500);
}
void firebaseinit(){
  firebaseConfig.host = firebasehost;
  firebaseConfig.signer.tokens.lgacy_token = firebaseauth;
  Firebase.begin(&firebseConfig,&firebaseauth);
  Firebase.reconnectWiFi(true)
  }
