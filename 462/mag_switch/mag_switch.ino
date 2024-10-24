void setup() {
  pinMode(16,INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(16) == HIGH){
    Serial.println("OPEN");

  }
  else{
    Serial.println("CLOSED");
    }
delay(1000);
}
