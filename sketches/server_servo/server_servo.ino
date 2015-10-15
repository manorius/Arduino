//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY

#include <Ethernet.h>
#include <SPI.h>
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
boolean reading = false;


////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
  byte ip[] = { 192, 168, 1, 40 };   //Manual setup only
  //byte gateway[] = { 192, 168, 0, 1 }; //Manual setup only
  //byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////

void setup(){
  myservo.attach(14);
  Serial.begin(9600);


  Ethernet.begin(mac,ip);
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

          triggerServo(c,client);

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

void triggerServo(int val, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
  client.print("<form name='input' method='get'>");
   client.print("LED: <input type='text' name='pin' />");
client.print("<input type='submit' value='Submit' />");
client.print("</form>");
Serial.println("------");
Serial.println(val);
myservo.write(val);                  // sets the servo position according to the scaled value 
  delay(15);                           // waits for the servo to get there 
  
}
