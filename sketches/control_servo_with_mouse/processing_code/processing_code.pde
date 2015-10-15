// Use the included processing code serial library
import processing.serial.*;        

Serial port;                         // The serial port

int spos=90;

void setup() 
{
  size(720, 720);
  colorMode(RGB, 1.0);
  noStroke();
  rectMode(CENTER);
  frameRate(100);

  println(Serial.list()); // List COM-ports

  //select second com-port from the list
  port = new Serial(this, Serial.list()[0], 9600); 
  
port.bufferUntil('\n');
}

void serialEvent(Serial myPort)
{
  boolean validString = true;  // whether the string you got is valid
  String errorReason = "";     // a string that will tell what went wrong

  // read the serial buffer:
  String myString = port.readStringUntil('\n');

  // make sure you have a valid string:

  if (myString != null)
  {
     println("Received: [" + myString + "]");
  }
}

void draw() 
{
  background(0.0);
  update(mouseX); 
}

int tempMouseX = 0;

void update(int x) 
{
  //Calculate servo postion from mouseX
  spos= x/4;
  
  if(tempMouseX != spos)
  {
  

  //Output the servo position ( from 0 to 180)
  
  port.write(spos); 
//print(spos+"\n");
  }
tempMouseX = spos;
}

