#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

int redPin = 6;
int greenPin = 5;
int bluePin = 3;

void setup()
{
  //AriasLantern
  Serial.begin(9600);
Serial.println("SERIAL STARTED!");
mySerial.begin(9600);/*
delay(1000);
mySerial.print("AT");
delay(1000);
mySerial.print("AT+VERSION");
delay(1000);
//mySerial.print("AT+PIN1342"); // Set pin to 1342
//delay(1000);
mySerial.print("AT+NAMEAriasLantern"); // Set the name to FresaBT
delay(1000);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
  setColourRgb(0,0,0);*/
}
 
void loop()
{
  unsigned red = 0;
  unsigned green = 0;
  unsigned blue = 0;
  
  int r = 0;
int g = 0;
int b = 0;

if (mySerial.find("c")) {
    red = mySerial.parseInt(); // parses numeric characters before the comma
    green = mySerial.parseInt();// parses numeric characters after the comma
    blue = mySerial.parseInt(); // parses numeric characters before the comma
    
    // print the results back to the sender:
    Serial.print("Setting color to: " );
    Serial.print(red);
    Serial.print(", ");
    Serial.print(green);
    Serial.print(", ");
    Serial.println(blue);
    // set the LED:
   // solid(red, green, blue);
r = 255-red;
g = 255-green;
b = 255-blue;
  
     analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

    Serial.print("--");
Serial.print(r);
    Serial.print(", ");
    Serial.print(g);
    Serial.print(", ");
    Serial.println(b);
        Serial.print("--");

}
 
void setColourRgb(unsigned int red, unsigned int green, unsigned int blue) {

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
 }

