void setup() {
  pinMode(4, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
    digitalWrite(4, digitalRead(3));
}
