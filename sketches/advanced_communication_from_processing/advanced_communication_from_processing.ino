//BinaryDataFromProcessing

#define HEADER	'|' 
#define MOUSE	'M' 
#define MESSAGE_BYTES 5 // the total bytes in a message

void setup() {
Serial.begin(115200);
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
    int val = Serial.read() * 256;
    val = val + Serial.read(); 
    Serial.print("Received mouse msg, index = "); 
    Serial.print(index); 
    Serial.print(", value ");
    Serial.println(val);
  }
  else
  {
    Serial.print("got message with unknown tag ");
    Serial.println(tag);
  }
}
   
 } 
  
}

