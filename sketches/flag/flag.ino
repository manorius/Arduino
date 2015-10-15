/* HC-SR04 Sensor
   https://www.dealextreme.com/p/hc-sr04-ultrasonic-sensor-distance-measuring-module-133696
  
   This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
   distance to the closest object in range. To do this, it sends a pulse
   to the sensor to initiate a reading, then listens for a pulse 
   to return.  The length of the returning pulse is proportional to 
   the distance of the object from the sensor.
     
   The circuit:
	* VCC connection of the sensor attached to +5V
	* GND connection of the sensor attached to ground
	* TRIG connection of the sensor attached to digital pin 2
	* ECHO connection of the sensor attached to digital pin 4


   Original code for Ping))) example was created by David A. Mellis
   Adapted for HC-SR04 by Tautvidas Sipavicius

   This example code is in the public domain.
 */

#include <Servo.h> 
const int trigPin = 2;
const int echoPin = 4;
int potPin = 0;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor
int lookDistance = 0;
int led = 13;
int detected = 0;
// THIS IS THE TIMER, COUNTING MILISECONDS SINCE THE START OF THE ARDUINO
long time = 0;
// AFTER HOW MANY MILLIS SHOULD WE CHECK
long checkPoint = 0;
// AMOUNT OF TIME BETWEEN CHECKS
int delayTime = 1000;
// NUMBER OF TIMES AN OBJECT IS INDSIDE THE PREDEFINED AREA OR OUTSIDE
int insideCounts = 0;
int outsideCounts = 0;

Servo myservo;  // create servo object to control a servo 


void setup() {
  // initialize serial communication:
  Serial.begin(9600);
    // initialize the digital pin as an output.
  pinMode(led, OUTPUT); 

   myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
   

}

void timeo(int inside,int outside)
{

// UPDATE TIMER
time = millis();

// CHECK IF THE TIMER HAS REACHED THE CHECKPOINT
if(time>=checkPoint)
{
  
  Serial.println("time reached");
  Serial.println(insideCounts);
  Serial.println(outsideCounts);

// CHECK IF IN THE ELAPSED TIME IT HAS BEEN INSIDE OR OUTSIDE, IF BOTH BEHAVE AS IF OUTSIDE 
 if(insideCounts==0 || (insideCounts!=0 && outsideCounts!=0))
 {
  digitalWrite(led, LOW);
  myservo.write(90);
  
 } 
 else if(outsideCounts==0)
 {
  digitalWrite(led, HIGH);
  myservo.write(180);
 // myservo.write(0);
 
 }
 
 Serial.println(time);
 Serial.println(checkPoint);
 
  // RESET
  checkPoint    = time+delayTime;
  insideCounts  = 0;
  outsideCounts = 0;
}
else
{
  insideCounts  += inside;
  outsideCounts += outside;
 // Serial.println("counting");
  
 
}

}

void loop()
{
 
  
  // Potentiometer
  val = analogRead(potPin);    // read the value from the sensor
  lookDistance = map(val,0,730, 0,360 );
  // establish variables for duration of the ping, 
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);


// CHECK IF INSIDE OR OUTSIDE OF THE SPECIFIED DISTANCE
 if(cm<=lookDistance){
  
   timeo(1,0);
   

 }
 else if(cm>=lookDistance){
  
   timeo(0,1);
  
 }
  
  delay(100);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
