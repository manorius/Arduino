int sensorPin = A2;    // select the input pin for the potentiometer
//int ledPin = 13;      // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
 // Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);    
  // turn the ledPin on
  //digitalWrite(ledPin, HIGH);  
  // stop the program for <sensorValue> milliseconds:
  // turn the ledPin off:        
//  digitalWrite(ledPin, LOW);   
  // stop the program for for <sensorValue> milliseconds:
 // Serial.println(sensorValue);
  int thisPitch = map(sensorValue, 400, 1000, 100, 1000);
  tone(5, thisPitch);
  delay(1);        // delay in between reads for stability
  
}
