/*
  Pitch follower
 
 Plays a pitch that changes based on a changing analog input
 
 circuit:
 * 8-ohm speaker on digital pin 8
 * photoresistor on analog 0 to 5V
 * 4.7K resistor on analog 0 to ground
 
 created 21 Jan 2010
 modified 9 Apr 2012
 by Tom Igoe 

This example code is in the public domain.
 
 http://arduino.cc/en/Tutorial/Tone2
 
 */
 #include "pitches.h"

void setup() {
  // initialize serial communications (for debugging only):
  Serial.begin(9600);
}

void loop() {
  // read the sensor:
  int sensorReading = analogRead(A0);
  // print the sensor reading so you know its range
  Serial.println(sensorReading);
  // map the pitch to the range of the analog input.
  // change the minimum and maximum input numbers below
  // depending on the range your sensor's giving:
  
  int noteDuration = 1000/8;
if(sensorReading<=200 && sensorReading>=0)
{
    Serial.println("NOTHING");
    noTone(8);
}
else if(sensorReading<=1024 && sensorReading>=200)
{
 sensorReading = map(sensorReading, 200, 1024, 0,4978); 
 tone(8, sensorReading);
 
}
/*else if(sensorReading<=500 && sensorReading>=200)
{
  Serial.println("first");
  tone(8, NOTE_C4);
}
  
else if(sensorReading<=1000 && sensorReading>=500)
{
  Serial.println("SECOND");
  tone(8, NOTE_G3);
}*/

int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
   // noTone(8);
  // play the pitch:
         // delay in between reads for stability
}






