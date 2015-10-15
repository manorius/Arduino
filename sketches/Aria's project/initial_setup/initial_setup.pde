/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

int pressstate2 = 0;
int pressstate3 = 0;
int pressstate4 = 0;
int pressstate5 = 0;
int pressstate6 = 0;

void setup() {
  Serial.begin(9600);
    pinMode(2, INPUT);
  digitalWrite(2, LOW);
  pinMode(3, INPUT);
  digitalWrite(3, LOW);
  pinMode(4, INPUT);
  digitalWrite(4, LOW);
pinMode(5, INPUT);
  digitalWrite(5, LOW);
  pinMode(6, INPUT);
  digitalWrite(6, LOW);
}

void loop() {
 /* int sensorValue2 = digitalRead(2);
  int sensorValue3 = digitalRead(3);
  int sensorValue4 = digitalRead(4);
  int sensorValue5 = digitalRead(5);
  int sensorValue6 = digitalRead(6);
  Serial.print("note A");
  Serial.println(sensorValue2, DEC);
  Serial.print("note B");
  Serial.println(sensorValue3, DEC);
  Serial.print("note C");
  Serial.println(sensorValue4, DEC);
  Serial.print("note D");
  Serial.println(sensorValue5, DEC);
  Serial.print("note E");
  Serial.println(sensorValue6, DEC);*/
  NotePressed();
  delay(1000);
}

void NotePressed()
{
  
 Serial.println("Note has been pressed"); 
  
  
}



