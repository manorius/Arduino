//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY

#include <Ethernet.h>
#include <SPI.h>
boolean reading = false;

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
  byte ip[] = { 192, 168, 0, 40 };   //Manual setup only
  //byte gateway[] = { 192, 168, 0, 1 }; //Manual setup only
  //byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);

  //Pins 10,11,12 & 13 are used by the ethernet shield

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  Ethernet.begin(mac);
  //Ethernet.begin(mac, ip, gateway, subnet); //for manual setup

  server.begin();
  Serial.println(Ethernet.localIP());

}

void loop(){

  // listen for incoming clients, and process qequest.
  checkForClient();

}

void checkForClient(){

  EthernetClient client = server.available();

  if (client) {

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean sentHeader = false;

    while (client.connected()) {
      if (client.available()) {

        if(!sentHeader){
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          sentHeader = true;
        }

        char c = client.read();
       
        if(reading && c == ' ') reading = false;
        if(c == '?') reading = true; //found the ?, begin reading the info

         // Serial.print(c);
          
        if(reading){

           switch (c) {
            case 'pin=2':
              //add code here to trigger on 2
              triggerPin(2, client);
              Serial.print("it's 2");
              break;
            case 'pin=3':
            //add code here to trigger on 3
              triggerPin(3, client);
              
              Serial.print("it's 3");
              break;
            case 'pin=4':
            //add code here to trigger on 4
              triggerPin(4, client);
              
              Serial.print("it's 4");
              break;
            case 'pin=5':
            //add code here to trigger on 5
              triggerPin(5, client);
              
              Serial.print("it's 5");
              break;
          }

        }

        if (c == '\n' && currentLineIsBlank)  break;

        if (c == '\n') {
          currentLineIsBlank = true;
        }else if (c != '\r') {
          currentLineIsBlank = false;
        }

      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  } 

}
int LEDstate[] = {0,0,0,0};
void triggerPin(int pin, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
  client.print("<form name='input' method='get'>");
   client.print("LED: <input type='text' name='pin' />");
client.print("<input type='submit' value='Submit' />");
client.print("</form>");

  
  int pointer = pin - 2;
 
  if(LEDstate[pointer]==0)
  {
    LEDstate[pointer]=1;
  digitalWrite(pin, HIGH);
  delay(25);
}
else
{
  LEDstate[pointer]=0;
  digitalWrite(pin, LOW);
  delay(25);
}
}
