#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <FirebaseESP32.h>
#include <WiFi.h>

// Define Firebase credentials
#define FIREBASE_HOST "iot-462-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "xmRBbGWVw94DscB36bvg9eDr3VMlaTA5GZWpGG3P"


// WiFi credentials
const char* ssid = "Nothing Phone (2a) 5G";         // Your WiFi SSID
const char* password = "9705991317"; // Your WiFi password

// Define I2C pins
#define I2C_SDA 21
#define I2C_SCL 22

// Create objects
Adafruit_BMP280 bmp;
Adafruit_SSD1306 display(128, 64, &Wire, -1);
FirebaseData firebaseData;

// Setup your Firebase
void setup() {
  Serial.begin(115200);
  
  // Initialize I2C
  Wire.begin(I2C_SDA, I2C_SCL);
  
  // Initialize BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }

  // Initialize OLED
  display.begin(SSD1306_I2C_ADDRESS, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi();
}

void loop() {
  // Read sensor data
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // in hPa
  float altitude = bmp.readAltitude(1013.25); // Adjusted to sea level pressure

  // Convert temperature to Fahrenheit
  float temperatureF = (temperature * 9.0 / 5.0) + 32.0;

  // Display on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.print(" C");
  display.print(" / ");
  display.print(temperatureF);
  display.print(" F");
  
  display.setCursor(0, 20);
  display.print("Pressure: ");
  display.print(pressure);
  display.print(" hPa");

  display.setCursor(0, 40);
  display.print("Altitude: ");
  display.print(altitude);
  display.print(" m");

  display.display();

  // Send data to Firebase
  Firebase.setFloat(firebaseData, "/temperature", temperature);
  Firebase.setFloat(firebaseData, "/temperatureF", temperatureF);
  Firebase.setFloat(firebaseData, "/pressure", pressure);
  Firebase.setFloat(firebaseData, "/altitude", altitude);

  delay(2000); // Update every 2 seconds
}
