#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <FirebaseESP32.h>

Adafruit_MPU6050 mpu;

#define WIFI_SSID "Nothing Phone (2a) 5G"
#define WIFI_PASSWORD "9705991317"

FirebaseConfig config;
FirebaseAuth auth;

#define FIREBASE_HOST "https://iot-462-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"

FirebaseData firebaseData;

void setup() {
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("Setup complete");
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Accel X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Accel Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Accel Z: ");
  Serial.println(a.acceleration.z);

  
  Serial.print("Gyro X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Gyro Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Gyro Z: ");
  Serial.println(g.gyro.z);


  if (Firebase.ready()) {
    Firebase.setFloat(firebaseData, "/MPU6050/accel_x", a.acceleration.x);
    Firebase.setFloat(firebaseData, "/MPU6050/accel_y", a.acceleration.y);
    Firebase.setFloat(firebaseData, "/MPU6050/accel_z", a.acceleration.z);
    Firebase.setFloat(firebaseData, "/MPU6050/gyro_x", g.gyro.x);
    Firebase.setFloat(firebaseData, "/MPU6050/gyro_y", g.gyro.y);
    Firebase.setFloat(firebaseData, "/MPU6050/gyro_z", g.gyro.z);
  }

  delay(1000);
}
