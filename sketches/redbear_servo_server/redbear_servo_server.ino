// UDP Port used for two way communication
unsigned int localPort = 8888;
Servo myservo;  // create servo object to control a servo
char packetBuffer[255]; //buffer to hold incoming packet
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An UDP instance to let us send and receive packets over UDP
UDP Udp;

void setup() {
    myservo.attach(D8);  // attaches the servo on pin 8 to the servo object
  // start the UDP
  Udp.begin(localPort);

  // Print your device IP Address via serial
  Serial.begin(115200);
  Serial.println(WiFi.localIP());
}

void loop() {
   // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remoteIp = Udp.remoteIP();
    Serial.print(remoteIp);
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0) packetBuffer[len] = 0;
    Serial.println("Contents:");
    Serial.println(packetBuffer); 
    
    String item = "123123";

    for(int k=0; k<len; k++){
      //item += String(packetBuffer[k]);
       //Serial.println( packetBuffer[k] );
       Serial.println( "-" );
      }
      char rotation[3] = {packetBuffer[3],packetBuffer[4],packetBuffer[5]};
      int rotate = atoi(rotation);
      Serial.println( rotate );
      myservo.write(rotate); 
//      Serial.println(item.toInt());
//      unsigned long highWord = packetBuffer[41];
    //  Serial.println( Udp.parseInt()  );
    //Serial.println( (int)item );

    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}
