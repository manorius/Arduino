/* * SerialReceive sketch * Blink the LED at a rate proportional to the received digit value
*/ 
 #include <Servo.h> 
const int ledPin = 13; 
Servo myservo;  // create servo object to control a servo 
// pin the LED is connected to 
int	blinkRate=0;	// blink rate stored in this variable
void setup() {
Serial.begin(115200); 
// Initialize serial port to send and receive at 9600 baud 
pinMode(ledPin, OUTPUT); // set this pin as output
myservo.attach(9);
} 

int value;
int sign = 1;

void loop()
{
 if( Serial.available())
 {
   
  char ch = Serial.read();
  //Serial.println(ch);
  if(ch >= '0' && ch <= '9')//is this an ascii digit between 0 and 9?
  {
    
    value = (value * 10) + (ch - '0'); // yes, accumulate the value
    
  }
  else if( ch == '-')
sign = -1;
  else// this assumes any char not a digit or minus sign terminates the value
  {
    value = value * sign ; // set value to the accumulated value 
    Serial.println(value); 
    myservo.write(value);
    value = 0; // reset value to 0 ready for the next sequence of digits 
    sign = 1;
  }
  
 } 
 blink();
}



// blink the LED with the on and off times determined by blinkRate 
void blink() 
{
digitalWrite(ledPin,HIGH); 
delay(blinkRate); // delay depends on blinkrate value 
digitalWrite(ledPin,LOW); 
delay(blinkRate);
}
