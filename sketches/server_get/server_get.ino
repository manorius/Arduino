/* Web_Parms_1.pde - very simple Webduino example of parameter passing and parsing */

/*
 * This is mostly a tool for testing and debugging the library, but can
 * also be used as an example of coding for it.
 *
 * To use it,  enter one of the following USLs into your browser.
 * Replace "host" with the IP address assigned to the Arduino.
 *
 * http://host/
 * http://host/index.html
 *
 * These return a "success" HTTP result and display the parameters
 * (if any) passed to them as a single string,  without attempting to
 * parse them.  This is done with a call to defaultCmd.
 * 
 * 
 * http://host/raw.html
 *
 * This is essentially the same as the index.html URL processing,
 * but is done by calling rawCmd.
 * 
 * 
 * http://host/result.html
 *
 * This invokes resultCmd,  which displays the "raw" parameter string,
 * but also uses the "nexyURLparam" routine to parse out the individual
 * parameters, and display them.
 */


#define WEBDUINO_FAIL_MESSAGE "<h1>Request Failed</h1>"
#include "SPI.h" // new include
#include "avr/pgmspace.h" // new include
#include "Ethernet.h"
#include "WebServer.h"

#define VERSION_STRING "0.1"

/*
//SERVO STUFF
*/
#include <Servo.h>

Servo servo1;
const int buttonPin = 13;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

/* CHANGE THIS TO YOUR OWN UNIQUE VALUE.  The MAC number should be
 * different from any other devices on your network or you'll have
 * problems receiving packets. */
static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };


/* CHANGE THIS TO MATCH YOUR HOST NETWORK.  Most home networks are in
 * the 192.168.0.XXX or 192.168.1.XXX subrange.  Pick an address
 * that's not in use and isn't going to be automatically allocated by
 * DHCP from your router. */
static uint8_t ip[] = { 192, 168, 1, 200 };

// ROM-based messages used by the application
// These are needed to avoid having the strings use up our limited
//    amount of RAM.

P(Page_start) = "<html><head><title>Web_Parms_1 Version " VERSION_STRING "</title></head><body>\n";
P(Page_end) = "</body></html>";
P(Get_head) = "<h1>GET from ";
P(Post_head) = "<h1>POST to ";
P(Unknown_head) = "<h1>UNKNOWN request for ";
P(Default_head) = "unidentified URL requested.</h1><br>\n";
P(Raw_head) = "raw.html requested.</h1><br>\n";
P(result_head) = "result.html requested.</h1><br>\n";
P(Good_tail_begin) = "URL tail = '";
P(Bad_tail_begin) = "INCOMPLETE URL tail = '";
P(Tail_end) = "'<br>\n";
P(result_tail_begin) = "URL parameters:<br>\n";
P(result_item_separator) = " = '";
P(Params_end) = "End of parameters<br>\n";
P(Post_params_begin) = "Parameters sent by POST:<br>\n";
P(Line_break) = "<br>\n";



/* This creates an instance of the webserver.  By specifying a prefix
 * of "", all pages will be at the root of the server. */
#define PREFIX ""
WebServer webserver(PREFIX, 80);

#define NAMELEN 32
#define VALUELEN 32


long result = 0;

void indexCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  
  ///CREATING NUMBERS
  
  long no1Int = random(1,9999);
  long no2Int = random(1,9999);
  long no3Int = random(1,9999);
  long no4Int = random(1,9999);
  
  result = ( no1Int + no2Int - no3Int ) * no4Int;
  
  
  Serial.println( no1Int);
  String no1 = String(no1Int);
  String no2 = String(no2Int);
  String no3 = String(no3Int);
  String no4 = String(no4Int);
  
  String finalString = String("(" + no1+" + "+no2+" - "+no3+" ) * "+no4+" = ");
  
  String fRes = String(result);
// char test[0] = {'120'};
 //prog_uchar test[] = {'12'};
  
 //P(test) = "sss";
  
  //Serial.println(finalString);
  
  /* this defines some HTML text in read-only memory aka PROGMEM.
     * This is needed to avoid having the string copied to our limited
     * amount of RAM. */
    P(headLine1) = "<!DOCTYPE HTML>";
P(headLine2) = "<html>";
P(headLine3) = "<body>";
P(closingLine1) = "</body>";
P(closingLine2) = "</html>";

     P(formLine1) = "<form action='result.html' method='get'>";
P(formLine3) = "<input type='text' name='result' />";
P(formLine4) = "<input type='submit' value='Submit' />";
P(formLine5) = "</form>";
    
    /* this is a special form of print that outputs from PROGMEM */
    server.printP(headLine1);
    server.printP(headLine2);
    server.printP(headLine3);
    
    
    server.printP(formLine1);
    server.println(finalString);
    server.printP(formLine3);
    server.printP(formLine4);
    server.printP(formLine5);
    server.println(fRes);
    
    server.printP(closingLine1);
    server.printP(closingLine2);
}

void resetCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  /*
  //   MOVE SERVO
  */
  servo1.attach(14);   
  servo1.write(147);
}

void resultCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  URLPARAM_RESULT rc;
  char name[NAMELEN];
  int  name_len;
  char value[VALUELEN];
  int value_len;

  /* this line sends the standard "we're all OK" headers back to the
     browser */
  server.httpSuccess();

  /* if we're handling a GET or POST, we can output our data here.
     For a HEAD request, we just stop after outputting headers. */
  if (type == WebServer::HEAD)
    return;

  server.printP(Page_start);
  switch (type)
    {
    case WebServer::GET:
        server.printP(Get_head);
        break;
   default:
        server.printP(Unknown_head);
    }

    server.printP(result_head);
    server.printP(tail_complete ? Good_tail_begin : Bad_tail_begin);
    server.print(url_tail);
    server.printP(Tail_end);

  if (strlen(url_tail))
    {
    server.printP(result_tail_begin);
    while (strlen(url_tail))
      {
      rc = server.nextURLparam(&url_tail, name, NAMELEN, value, VALUELEN);
      if (rc == URLPARAM_EOS)
        server.printP(Params_end);
       else
        {
        server.print(name);
        server.printP(result_item_separator);
        server.print(value);
        server.printP(Tail_end);
        Serial.println(value);
        
        String helloMsg =String("");
        String msg =String("");
        
        if(atol(value) == result)
        {
          helloMsg = "<h1>CORRECT! :)</h1>";
          msg = "<h2>enjoy your Double Bouble</h2>";
        }else
        {
          
          helloMsg = "<h1>INCORRECT! :(</h1>";
          msg = "<h2>no Double Bouble for you</h2>";
        }
    server.println(helloMsg);
    server.println(msg);
    
   
        }
      }
    }
  /*
  //   MOVE SERVO
  */
  servo1.attach(14);   
  servo1.write(147);
  
  server.printP(Page_end);

}

void my_failCmd(WebServer &server, WebServer::ConnectionType type, char *url_tail, bool tail_complete)
{
  /* this line sends the standard "we're all OK" headers back to the
     browser */
  server.httpFail();

  /* if we're handling a GET or POST, we can output our data here.
     For a HEAD request, we just stop after outputting headers. */
  if (type == WebServer::HEAD)
    return;

  server.printP(Page_start);
  switch (type)
    {
    case WebServer::GET:
        server.printP(Get_head);
        break;
    case WebServer::POST:
        server.printP(Post_head);
        break;
    default:
        server.printP(Unknown_head);
    }

    server.printP(Default_head);
    server.printP(tail_complete ? Good_tail_begin : Bad_tail_begin);
    server.print(url_tail);
    server.printP(Tail_end);
    server.printP(Page_end);

}




void setup()
{
  pinMode(1,OUTPUT);
  //servo1.attach(14); //analog pin 0
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT); 
  
  // initialize the serial communication:
  Serial.begin(9600);
  
  /* initialize the Ethernet adapter */
  Ethernet.begin(mac, ip);

  /* setup our default command that will be run when the user accesses
   * the root page on the server */
  webserver.setDefaultCommand( &indexCmd);

  /* setup our default command that will be run when the user accesses
   * a page NOT on the server */
  webserver.setFailureCommand(&my_failCmd);
  
  webserver.addCommand("index.html", &indexCmd);

  /* run the same command if you try to load /index.html, a common
   * default page name */
  webserver.addCommand("result.html", &resultCmd);
  
    /* run the same command if you try to load /index.html, a common
   * default page name */
  webserver.addCommand("reset.html", &resetCmd);


  /* start the webserver */
  webserver.begin();
}

int tempSwitch = 0;

void loop()
{
  char buff[64];
  int len = 64;
  
  buttonState = digitalRead(buttonPin);
  
  // CONTROLLING THE SERVO
  Serial.println("---");
Serial.println(buttonState);
Serial.println(tempSwitch);
  
if(buttonState == HIGH)
  {
    servo1.attach(14);   
  servo1.write(147);
   tempSwitch = 1; 
    Serial.println("HIGH");
  }
  else if(buttonState == LOW && tempSwitch == 1)
  {
    servo1.detach();
    tempSwitch = 0;
    Serial.println("LOW");
  }
Serial.println("---");
  /* process incoming connections one at a time forever */
  webserver.processConnection(buff, &len);
}
