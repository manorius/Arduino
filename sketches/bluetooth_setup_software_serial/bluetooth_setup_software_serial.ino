#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup()
{
Serial.begin(9600);
Serial.println("SERIAL STARTED!");
mySerial.begin(9600);
delay(1000);
mySerial.print("AT");
delay(1000);
mySerial.print("AT+VERSION");
delay(1000);
//mySerial.print("AT+PIN1342"); // Set pin to 1342
//delay(1000);
mySerial.print("AT+NAMECharger2"); // Set the name to FresaBT
delay(1000);
//mySerial.print("AT+BAUD8"); // Set baudrate to 115200
///mySerial.print("AT+BAUD4"); // Set baudrate to 9600
//delay(1000);
}

int n=0;

void loop()
{

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
 // if (buttonState == HIGH) n++;  
  
// READING RECEIVED BYTES  
 if (mySerial.available())
{ 
mySerial.print("YOU SENT: ");
while(mySerial.available())
mySerial.println(mySerial.read());
}
delay(2000);
// SENDING BYTES
mySerial.print("\n");
  mySerial.print("CABBd");
mySerial.print("\n");
// EXCHANGING DATA BETWEEN S
/*if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());
*/    
} 
