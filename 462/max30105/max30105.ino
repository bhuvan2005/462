#include <Wire.h>
#include "MAX30105.h"

#include "heartRate.h"

MAX30105 particleSensor;

const byte ratesize = 4;
byte rates[ratesize];
byte rateSpot = 0;
long lastBeat = 0;
float bpm;
int bavg;

void setup()
{
  Serial.begin(115200);
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
}

void loop()
{
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
}
