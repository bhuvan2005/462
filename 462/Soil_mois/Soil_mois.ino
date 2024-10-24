void setup() {
 Serial.begin(9600);
}

void loop() {
  int sm = 4095 - analogRead(34);
  Serial.println(sm);
  delay(500);

}
