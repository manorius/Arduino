#include <Servo.h>

Servo servo1;
const int buttonPin = 13;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status


void setup() {

  pinMode(1,OUTPUT);
  servo1.attach(14); //analog pin 0
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);   
  
  Serial.begin(9600);
  Serial.println("Ready");

}

int time = 0;
int bClicked = 0;
int switcher = 0;

void loop() {
// read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
Serial.println(buttonState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if(buttonState == HIGH)
  {
    if(switcher==0)
    {
      switcher = 1;
     bClicked = 1;
    }
   else
  {
   switcher = 0;
   bClicked = 0;
  } 
  }
  
  if (bClicked == 1 ) {  
    time++;
    Serial.println(time);
    servo1.attach(14);   
    servo1.write(147);
    // turn LED on:    
    // digitalWrite(ledPin, HIGH);  
  } 
  else {
    bClicked = 0;
    time = 0;
    servo1.detach();
    // turn LED off:
    //digitalWrite(ledPin, LOW); 
  }
 
//

delay(10);

} 
