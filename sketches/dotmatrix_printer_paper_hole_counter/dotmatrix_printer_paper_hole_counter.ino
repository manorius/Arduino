int input = A0;
 
int sensorValue = 0;
int highValue = 0;
int lowValue  = 0; 
int holes = 0;
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers


void setup()
{
Serial.begin(9600);
}
 
void loop()
{
sensorValue =analogRead(input);
 
//Serial.print("Value = " );
//Serial.println(sensorValue);
if(sensorValue>250)
{

//Serial.println("High");
highValue++;
lowValue = 0;
 lastDebounceTime = millis();
}
else if(sensorValue<250)
{
 
  //Serial.println(millis() - lastDebounceTime);
  if((millis() - lastDebounceTime) > debounceDelay){
  if(lowValue==0)
{
  holes++;
  Serial.println(String(holes)+" Holes detected");
}
//Serial.println(String(lowValue)+" Low Value");
 // Serial.println("Last HighValue = "+String(highValue)+" Low");
  lowValue ++;
  highValue = 0;
}
}
 
}
