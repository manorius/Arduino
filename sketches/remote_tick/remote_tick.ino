/*
 * This is a minimal example, see extra-examples.cpp for a version
 * with more explantory documentation, example routines, how to
 * hook up your pixels and all of the pixel types that are supported.
 *
 */
#if defined(ARDUINO) 
SYSTEM_MODE(SEMI_AUTOMATIC); 
#endif

int led1 = D8;
int led2 = D7;

// your network name also called SSID
char ssid[] = "digitalnihilist";
// your network password
char password[] = "manorius1234";
// your network key Index number (needed only for WEP)
int keyIndex = 0;
String readString;

TCPServer server(80);

void printWifiStatus();

void setup()
{
  ////////////////////
  // PIN RELATED    //
  ////////////////////
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
    
  ////////////////////
  // SERVER RELATED //
  ////////////////////
  
  Serial.begin(115200); // initialize serial communication
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
          Serial.print(c);
         }

         //if HTTP request has ended
         if (c == '\n') {          
          // Serial.println(readString);

         // LISTEN FOR CLICK REQUEST
         if (readString.indexOf("?tick") >0){
          Serial.println("TICK");
          digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);

  delay(100);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
         }
         
         // REPLY TO HTTP REQUEST
         client.println("HTTP/1.1 202 OK");
         client.println("Access-Control-Allow-Origin: *");
         client.println("Received");
         delay(1);
         //stopping client
         client.stop();
         //Serial.println(readString);
         readString="";
        }
       }
       //client.println("hello");
    }
}

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


