/* * SerialReceive sketch * Blink the LED at a rate proportional to the received digit value
*/ 
 #include <Servo.h> 
 #define HEADER	'|' 
#define MOUSE	'M' 
#define MESSAGE_BYTES 6 // the total bytes in a message

Servo myservo1;  // create servo object to control a servo 
Servo myservo2;  // create servo object to control a servo 
int led1 = 2;
int led2 = 3;

void setup() {
Serial.begin(115200);
// SET THE LIGHTS
pinMode(led1, OUTPUT);
pinMode(led2, OUTPUT); 
 digitalWrite(led1, LOW); 
    digitalWrite(led2, LOW); 
// Initialize serial port to send and receive at 9600 baud 
// head
myservo1.attach(9);
// arm
myservo2.attach(10);

myservo1.write(180);
    myservo2.write(150);
} 

void loop()
{
 
 if ( Serial.available() >= MESSAGE_BYTES) 
 {
  if( Serial.read() == HEADER)
{
  char tag = Serial.read(); 
  if(tag == MOUSE)
  {
    int index = Serial.read(); // this was sent as a char but it's ok to use it as an int
    int val = Serial.read();
    int light1 = Serial.read();
    int light2 = Serial.read();
    
    Serial.print("Received mouse msg, index = "); 
    Serial.print(index); 
    Serial.print(", value ");
    Serial.println(val);
    Serial.print(", LIGHTS ");
    Serial.print(light1);
    Serial.print(light2);
    
    myservo1.write(index);
    myservo2.write(val);
    
    if(light1==1 && light2==1)
    {
     digitalWrite(led1, HIGH); 
    digitalWrite(led2, HIGH);  
    }
    else
    {
      digitalWrite(led1, LOW); 
    digitalWrite(led2, LOW); 
    }
    
  }
  else
  {
    Serial.print("got message with unknown tag ");
    Serial.println(tag);
  }
}
   
 } 
  
}

