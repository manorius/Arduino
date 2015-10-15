#include <Servo.h>

Servo servo1;
Servo servo2;


void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(14); //analog pin 0
  servo2.attach(15); //analog pin 1
  
  Serial.begin(9600);

}

void loop() {
if ( Serial.available()) {
  int pos = Serial.read(); 
servo1.write(pos);
servo2.write(pos);
Serial.println(pos);
}

} 
