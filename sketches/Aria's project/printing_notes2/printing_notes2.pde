/*
  DigitalReadSerial
 Reads a digital input on pin 2, prints the result to the serial monitor 
 
 This example code is in the public domain.
 */

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
}

void notecondition(int note,int prevNote,String letter)
{
  if(note!=prevNote) {
   Serial.print("\n");
 if(note) 
 Serial.print( "NOTE "+letter+" has been pressed" ); 
 else
 Serial.print("NOTE "+letter+" has been released"); 
 }
  
}


void NotePressed(int a, int b, int c, int d, int e)
{
  int notes[]   = {a,b,c,d,e};
  char letters[] = {"A","B","C","D","E"};
  
  for (int i=0; i <= sizeof(notes); i++){
      notecondition(notes[i],previousPressstate[i],letters[i] );
      previousPressstate[i]=notes[i];
   }  

 
}




