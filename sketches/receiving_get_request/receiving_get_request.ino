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
char ssid[] = "digitalnihilist";
// your network password
char password[] = "manolis123456";
// your network key Index number (needed only for WEP)
int keyIndex = 0;
String HTTPget = "";
TCPServer server(80);

void printWifiStatus();

// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 100;
// the maximum length of paramters we accept
const int MAX_PARAM = 10;
boolean reading = false;
void setup()
{
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

 }
 


void loop()
{
  boolean lineIsBlank = true;
  // listen for incoming clients
  TCPClient client = server.available();
  if (client) {
    char c = client.read();
    if(reading && c == ' ') reading = false;
      if(c == '?') reading = true; // ? in GET request was found, start reading the info
 
      //check that we are reading, and ignore the '?' in the URL, then append the get parameter into a single string
      if(reading && c != '?') HTTPget += c;
 
      if (c == '\n' && lineIsBlank)  return;
 
      if (c == '\n')
      {
        lineIsBlank = true;
      }
      else if (c != '\r')
      {
        lineIsBlank = false;
      }

      Serial.println(HTTPget);

  }
  client.print(HTTPget);
  delay(1); // give the web browser a moment to recieve
  client.stop(); // close connection
  HTTPget = ""; // clear out the get param we saved
}

 

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


