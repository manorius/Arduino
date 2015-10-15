/*
  Twitter Client with Strings
 
 This sketch connects to Twitter using an Ethernet shield. It parses the XML
 returned, and looks for <text>this is a tweet</text>
 
 You can use the Arduino Ethernet shield, or the Adafruit Ethernet shield, 
 either one will work, as long as it's got a Wiznet Ethernet module on board.
 
 This example uses the DHCP routines in the Ethernet library which is part of the 
 Arduino core from version 1.0 beta 1
 
 This example uses the String library, which is part of the Arduino core from
 version 0019.  
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 21 May 2011
 modified 9 Apr 2012
 by Tom Igoe
 
 This code is in the public domain.
 
 */
 #include <MemoryFree.h>
#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"
#include <Servo.h>

Servo servo1;
const int stopServoPin = 13;

int stopServoState = 0;    

int printer_RX_Pin = 5;  // this is the green wire
int printer_TX_Pin = 6;  // this is the yellow wire

Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 };
IPAddress ip(192,168,1,21);

// initialize the library instance:
EthernetClient client;

const unsigned long requestInterval = 6000;  // delay between requests

char serverName[] = "pubsub.pubnub.com";  // twitter URL

boolean requested;                   // whether you've made a request since connecting
unsigned long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds

String currentLine = "";            // string to hold the text from server
String previousTweet = "";
String tweet = "";                  // string to hold the tweet
boolean readingTweet = false;       // if you're currently reading the tweet

String msg = "";                  // string to hold the msg
String previousMSG = "";            // for comparing the messages 
boolean readingmsg = false;       // if you're currently reading the msg

void setup() {
  // reserve space for the strings:
  currentLine.reserve(256);
  tweet.reserve(150);
  
  
 // initialize the pushbutton pin as an input:
  pinMode(stopServoPin, INPUT);
  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // attempt a DHCP connection:
  Serial.println("Attempting to get an IP address using DHCP:");
  if (!Ethernet.begin(mac)) {
    // if DHCP fails, start with a hard-coded address:
    Serial.println("failed to get an IP address using DHCP, trying manually");
    Ethernet.begin(mac, ip);
  }
  Serial.print("My address:");
  Serial.println(Ethernet.localIP());
  // connect to Twitter:
  connectToServer();
}

int tempSwitch = 0;

void dispenser()
{
  // read the state of the pushbutton value:
  stopServoState = digitalRead(stopServoPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if(stopServoState == HIGH)
  {
    servo1.attach(8);   
  servo1.write(147);
   tempSwitch = 1; 
    Serial.println("HIGH");
  }
  else if(stopServoState == LOW && tempSwitch == 1)
  {
    servo1.detach();
    tempSwitch = 0;
    Serial.println("LOW");
  }
  
  
  
  delay(1);        // delay in between reads for stability
}

void loop()
{
  dispenser();
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.connected()) {
  if (client.available()) {
   
    char inChar = client.read();
// add incoming byte to end of line:
      currentLine += inChar; 
//Serial.println(currentLine);
// if you get a newline, clear the line:
      if (inChar == '\n') {
        currentLine = "";
      } 
      // if the current line ends with ":, it will
      // be followed by the msg:
      if ( currentLine.endsWith("\":\"")) {
        // msg is beginning. Clear the msg string:
        readingmsg = true; 
        msg = "";
      }
      // if you're currently reading the bytes of a msg,
      // add them to the msg String:
      if (readingmsg) {
        if (inChar != '}') {
          msg += inChar;
        } 
        else if(previousMSG!=msg && msg!="") {
          // if you got a "}" character,
          // you've reached the end of the msg:
          readingmsg = false;
         //Serial.println(msg); 
        // printer.wake(); //Wake printer.
         previousMSG = msg;
         //        printer.println("--");
         //printer.println(previousMSG);
         Serial.println(msg);
         Serial.println("----------"); 
          servo1.attach(8);   
  servo1.write(147);
        // printer.sleep();
          // close the connection to the server:
          client.stop(); 
          
        }
        else{
     // Serial.println("MSG hasn't changed");
        client.stop(); 
      }
      }
}

  }
  else if (millis() - lastAttemptTime > requestInterval) {
    // if you're not connected, and two minutes have passed since
    // your last connection, then attempt to connect again:
    connectToServer();
  }
}

void connectToServer() {
  // attempt to connect, and wait a millisecond:
  // if you get a connection, report back via serial:
  Serial.println("connect to server");
  if (client.connect(serverName, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /history/sub-ac80994f-c74a-11e1-8c59-45462a68df37/testing/0/1 HTTP/1.0");
   client.println();
  }
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}
