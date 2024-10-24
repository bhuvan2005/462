#include<Wire.h>
#include "SSD1306.h"

SSD1306 display(0x3c,21,22);
String mystring;
const int trig = 25;
const int echo = 26;

long duration;
int distance;
int count;
void setup() {
  oledinit();
  pinMode(16,INPUT_PULLUP);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
}

void loop() {
  digitalWrite(trig,LOW);
 delayMicroseconds(2); 

 digitalWrite(trig,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig,LOW);

 duration = pulseIn(echo,HIGH);
 distance = duration*0.034/2;

 Serial.print("distance: ");
 Serial.println(distance);
  OLEDUpdate();
  delay(500);
}
void oledinit(){
  display.init();
  display.setFont(ArialMT_Plain_24);
  }
void OLEDUpdate(){
    display.clear();
    mystring = distance+"cm";
    display.drawString(0,0,mystring);
    display.display();
  }
