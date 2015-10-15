/*
  Web client
 
 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 
 created 18 Dec 2009
 modified 9 Apr 2012
 by David A. Mellis
 
 */
 #include <MemoryFree.h>
#include "SoftwareSerial.h"
#include "Adafruit_Thermal.h"

int printer_RX_Pin = 5;  // this is the green wire
int printer_TX_Pin = 6;  // this is the yellow wire

Adafruit_Thermal printer(printer_RX_Pin, printer_TX_Pin);

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192,168,0,20);

// Initialize the Ethernet client library
// with the IP address and port of the server 
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

const unsigned long requestInterval = 50;  // delay between requests
char serverName[] = "pubsub.pubnub.com";  // twitter URL

boolean requested;                   // whether you've made a request since connecting
unsigned long lastAttemptTime = 0;            // last time you connected to the server, in milliseconds

String currentLine = "";            // string to hold the text from server
String msg = "";                  // string to hold the msg
String previousMSG = "";            // for comparing the messages 
boolean readingmsg = false;       // if you're currently reading the msg

void setup() {
  printer.begin();
  printer.sleep();
  // reserve space for the strings:
  currentLine.reserve(256);
  msg.reserve(150);
  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  /* while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }*/

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
   Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
 connectToServer();
}

void loop()
{
  // if there are incoming bytes available 
  // from the server, read them and print them:
  if (client.connected()) {
  if (client.available()) {
  //  Serial.println(freeMemory());
   
    char inChar = client.read();
// add incoming byte to end of line:
      currentLine += inChar; 

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
         printer.setSize('M'); 
         printer.justify('C'); 
         //        printer.println("--");
         //printer.println(previousMSG);
         printer.println(msg); 
         printer.feed(1);
         printer.println("----------"); 
         printer.feed(1);
         
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
   // Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(serverName, 80)) {
   Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /history/sub-ac80994f-c74a-11e1-8c59-45462a68df37/testing/0/1 HTTP/1.0");
   client.println();
  } 
  else {
    // kf you didn't get a connection to the server:
    Serial.println("connection failed");
  } 
  // note the time of this connect attempt:
  lastAttemptTime = millis();
  
}
