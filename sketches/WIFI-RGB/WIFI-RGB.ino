/*
 * This is a minimal example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 */
#if defined(ARDUINO) 
SYSTEM_MODE(SEMI_AUTOMATIC); 
#endif

#include "application.h"
#include "neopixel.h" // use for Build IDE
// #include "neopixel.h" // use for local build

// your network name also called SSID
char ssid[] = "Schmiede";
// your network password
char password[] = "D69A13CCEA";
// your network key Index number (needed only for WEP)
int keyIndex = 0;
String readString;
int led = 7;

TCPServer server(80);

void printWifiStatus();

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_COUNT 30
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

// Prototypes for local build, ok to leave in for Build IDE
void rainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

void setup()
{
    pinMode(led, OUTPUT);
  ////////////////////
  // SERVER RELATED //
  ////////////////////
  
  Serial.begin(115200);      // initialize serial communication
    // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.on();
  WiFi.setCredentials(ssid,password);
  WiFi.connect();
  
  while (WiFi.connecting()) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  IPAddress localIP = WiFi.localIP();
  while (localIP[0] == 0) {
    localIP = WiFi.localIP();
    Serial.println("waiting for an IP address");
    delay(1000);
  }

  // you're connected now, so print out the status  
  printWifiStatus();
  
  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");

  ///////////////////////
  // LED STRIP RELATED //
  ///////////////////////
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
void loop()
{
  /////////////////////
  // STARTING SERVER //
  /////////////////////
  
  // listen for incoming clients
  TCPClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debuging
     
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
//           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
//           client.println("<TITLE>Random Nerd Tutorials Project</TITLE>");
client.println("<style>");
client.print("a{\ndisplay:inline-block;\nwidth:10px;\nheight:10px;\nborder:1px solid black;\n}\na.active\n{\nbackground-color:black;\n}");
client.println("</style>");
client.println("LED controller");
           client.println("</HEAD>");
           client.println("<BODY>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led0\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led1\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led2\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led3\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led4\"\"></a>");
client.println("<br>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led5\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led6\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led7\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led8\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led9\"\"></a>");
client.println("<br>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led10\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led11\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led12\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led13\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led14\"\"></a>");
client.println("<br>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led15\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led16\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led17\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led18\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led19\"\"></a>");
client.println("<br>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led20\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led21\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led22\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led23\"\"></a>");
client.println("<a class=\"\" style=\"background-color:rgb(0,0,0);\" href=\"/?led24\"\"></a>");
client.println("<br>");           
         //  client.println("<a href=\"/?button1on\"\">Turn On Blue LED</a>");
           client.println("</BODY>");
           client.println("</HTML>");
     
           delay(1);
           //stopping client
           client.stop();
           //controls the Arduino if you press the buttons
          if (readString.indexOf("?led0") >0){
                strip.setPixelColor(0, 255,0,0);
                strip.show();
           }
           if (readString.indexOf("?led1") >0){
                strip.setPixelColor(1, 255,0,0);
                strip.show();
           }
//           if (readString.indexOf("?button1off") >0){
//               digitalWrite(led, LOW);
//           }
//           if (readString.indexOf("?button2on") >0){
//                for(pos = 0; pos < 180; pos += 3)  // goes from 0 degrees to 180 degrees 
//                {                                  // in steps of 1 degree 
//                  microservo.write(pos);              // tell servo to go to position in variable 'pos' 
//                  delay(15);                       // waits 15ms for the servo to reach the position 
//                } 
//           }
//           if (readString.indexOf("?button2off") >0){
//                for(pos = 180; pos>=1; pos-=3)     // goes from 180 degrees to 0 degrees 
//                {                                
//                  microservo.write(pos);              // tell servo to go to position in variable 'pos' 
//                  delay(15);                       // waits 15ms for the servo to reach the position 
//                } 
//           }
            //clearing string for next read
            readString="";  
           
         }
       }
    }
}

 
  //rainbow(20);
}

//void rainbow(uint8_t wait) {
//  uint16_t i, j;
//
//  for(j=0; j<256; j++) {
//    for(i=0; i<strip.numPixels(); i++) {
//      strip.setPixelColor(i, Wheel((i+j) & 255));
//    }
//    strip.show();
//    delay(wait);
//  }
//}
//
//// Input a value 0 to 255 to get a color value.
//// The colours are a transition r - g - b - back to r.
//uint32_t Wheel(byte WheelPos) {
//  if(WheelPos < 85) {
//   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
//  } else if(WheelPos < 170) {
//   WheelPos -= 85;
//   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
//  } else {
//   WheelPos -= 170;
//   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
//  }
//}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("Network Name: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
