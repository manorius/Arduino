/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */
int pressstate2was = 1;
int pressstate3was = 1;
int pressstate4was = 1;
int pressstate5was = 1;
int pressstate6was = 1;


int previousPressstate[5];

void setup() {
  Serial.begin(9600);
    pinMode(2, INPUT);
  digitalWrite(2, LOW);
  pinMode(3, INPUT);
  digitalWrite(3, LOW);
  pinMode(4, INPUT);
  digitalWrite(4, LOW);
pinMode(5, INPUT);
  digitalWrite(5, LOW);
  pinMode(6, INPUT);
  digitalWrite(6, LOW);
}

void loop() {
  NotePressed(digitalRead(2),digitalRead(3),digitalRead(4),digitalRead(5),digitalRead(6));
  delay(100);
}



void NotePressed(int a, int b, int c, int d, int e)
{
  //Serial.print(a);
  //Serial.print(pressstate2was);
  if( a!=1 && pressstate2was==1 ) {
   
 Serial.print("Do \n");  
 }
 
 if( b!=1 && b!=pressstate3was ) {

 Serial.print("Re \n"); 
 }
 
if( c!=1 && c!=pressstate4was ) {

 Serial.print("Mi \n"); 
 }
 
if( d!=1 && d!=pressstate5was ) {

 Serial.print("Fa \n"); 
 }
 
if( e!=1 && e!=pressstate6was ) {

 Serial.print("Sol \n"); 
 }
 
pressstate2was = a;
pressstate3was = b;
pressstate4was = c;
pressstate5was = d;
pressstate6was = e;
 /*
 else
 if(b) Serial.print("NOTE B has been pressed"); 
 if(c) Serial.print("NOTE C has been pressed"); 
 if(d) Serial.print("NOTE D has been pressed"); 
 if(e) Serial.print("NOTE E has been pressed"); 
 */
 

 
}




