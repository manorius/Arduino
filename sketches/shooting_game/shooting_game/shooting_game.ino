#include <Servo.h> 

Servo myservo1;
int callibrationButton = 3;
int callibrate = 0;
int sensorPin = A0;   
int sensorValue = 0;  // variable to store the value coming from the sensor
int highestValue = 0;  // record highest value for autocalibration
int pos1 = 0;

void setup() {
  myservo1.attach(3);
   // initialize the pushbutton pin as an input:
  pinMode(callibrationButton, INPUT);
  // initialize serial:
  Serial.begin(9600);
}

void loop() {

  myservo1.write(0); 

// GET ANALOG VALUE  
sensorValue = analogRead(sensorPin);
// SET MAX SENSOR VALUE
highestValue = (sensorValue>highestValue)? sensorValue:highestValue;

// IF callibrate == 1 THEN START CALLIBRATION
callibrate = digitalRead(callibrationButton);

Serial.println("Highest Value: "+String(highestValue));
Serial.println("Sensor Value: "+String(sensorValue));
Serial.println("\n\r");
delay(800);
}
