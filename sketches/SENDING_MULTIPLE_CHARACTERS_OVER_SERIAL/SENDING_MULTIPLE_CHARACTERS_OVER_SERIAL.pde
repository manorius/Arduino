/* * SerialReceive sketch * Blink the LED at a rate proportional to the received digit value
*/ 
const int ledPin = 13; 
// pin the LED is connected to 
int	blinkRate=0;	// blink rate stored in this variable
void setup() {
Serial.begin(115200); 
// Initialize serial port to send and receive at 9600 baud 
pinMode(ledPin, OUTPUT); // set this pin as output
} 

int value;

void loop()
{
 if( Serial.available())
 {
   
  char ch = Serial.read();
  //Serial.println(ch);
  if (ch == 13) {Serial.println('ENTER HAS BEEN PRESSED');}
  if(ch >= '0' && ch <= '9')//is this an ascii digit between 0 and 9?
  {
    
    value = (value * 10) + (ch - '0'); // yes, accumulate the value
    
  }
  else if (ch == 101) // is the character the newline character
  {
    Serial.println("RETURN");
    blinkRate = value;
    Serial.println(blinkRate);
    value = 0;
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
