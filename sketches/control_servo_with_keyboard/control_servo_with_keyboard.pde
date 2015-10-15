/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
 #include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
 
 int val;    // variable to read the value from the analog pin 
int command;
void setup() {
  Serial.begin(9600);
  myservo.attach(9);
}

void loop() {
  //int sensorValue = analogRead(A0);
 // val = map(sensorValue, 0, 1023, 0, 179);     // scale it to use it with the servo (value between 0 and 180) 
 // Serial.println(sensorValue, DEC);
 if(Serial.available())
{
   command = Serial.read();
   Serial.println(command);
val = map(command, 49, 57, 0, 179);
Serial.println(val, DEC);
}
  myservo.write(val);
}
