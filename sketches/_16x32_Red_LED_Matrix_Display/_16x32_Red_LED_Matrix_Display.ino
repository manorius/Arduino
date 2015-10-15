/*
  Simple demo for SeeedStudio ultrathin 16x32 Red LED Screen 
  Displays Space Invader image stored in the 2D-array. 

  The circuit:
  * A connect to digital 2
  * B connect to digital 3
  * C connect to digital 4
  * D connect to digital 5
  * OE connect to digital 6
  * STB connect to digital 10
  * R1 connect to digital 11
  * CLK connect to digital 13
  * GND connect to GND
*/

#include <SPI.h>

#define RowA 2 
#define RowB 3 
#define RowC 4 
#define RowD 5 
#define OE 6
#define R1 11
#define CLK 12
#define STB 10

#define displayWidth 4
#define displayHeight 16

byte row=0; 
byte spaceInvader[displayHeight][displayWidth] =  
{ 
{B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000},
{B00000000,B00110000,B00001100,B00000000},
{B00000000,B00110000,B00001100,B00000000},
{B00000000,B00001111,B11110000,B00000000},
{B00000000,B00001111,B11110000,B00000000},
{B00000000,B00110011,B11001100,B00000000},
{B00000000,B00110011,B11001100,B00000000},
{B00000000,B00111111,B11111100,B00000000},
{B00000000,B00111111,B11111100,B00000000},
{B00000000,B00110011,B11001100,B00000000},
{B00000000,B00110011,B11001100,B00000000},
{B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000},
{B00000000,B00000000,B00000000,B00000000}
};

byte screenBuffer[displayHeight][displayWidth];
byte screen[displayHeight][displayWidth];
byte screenBuffer2[displayHeight][displayWidth];

float sines[]={
0.0,0.000304586,0.000685233,0.001217975,0.001902651,0.002739052,0.003726924,0.004865966,0.00615583,0.007596123,0.009186408,0.0109262,
0.012814968,0.014852137,0.017037087,0.019369152,0.021847622,0.024471742,0.027240712,0.03015369,0.033209787,0.036408073,0.039747573,
0.043227271,0.046846106,0.050602977,0.054496738,0.058526204,0.062690146,0.066987298,0.07141635,0.075975952,0.080664716,0.085481214,
0.090423978,0.095491503,0.100682245,0.105994623,0.111427019,0.116977778,0.12264521,0.128427587,0.134323149,0.1403301,0.146446609,
0.152670815,0.15900082,0.165434697,0.171970486,0.178606195,0.185339804,0.192169262,0.199092488,0.206107374,0.213211782,0.220403548,
0.227680482,0.235040368,0.242480963,0.25,0.25759519,0.265264219,0.27300475,0.280814427,0.288690869,0.296631678,0.304634436,0.312696703,
0.320816025,0.328989928,0.337215923,0.345491503,0.353814148,0.362181322,0.370590477,0.379039052,0.387524473,0.396044155,0.404595502,
0.413175911,0.421782767,0.43041345,0.439065328,0.447735768,0.456422129,0.465121763,0.473832022,0.482550252,0.491273797,0.5,0.508726203,
0.517449748,0.526167978,0.534878237,0.543577871,0.552264232,0.560934672,0.56958655,0.578217233,0.586824089,0.595404498,0.603955845,
0.612475527,0.620960948,0.629409523,0.637818678,0.646185852,0.654508497,0.662784077,0.671010072,0.679183975,0.687303297,0.695365564,
0.703368322,0.711309131,0.719185573,0.72699525,0.734735781,0.74240481,0.75,0.757519037,0.764959632,0.772319518,0.779596452,0.786788218,
0.793892626,0.800907512,0.807830738,0.814660196,0.821393805,0.828029514,0.834565303,0.84099918,0.847329185,0.853553391,0.8596699,
0.865676851,0.871572413,0.87735479,0.883022222,0.888572981,0.894005377,0.899317755,0.904508497,0.909576022,0.914518786,0.919335284,
0.924024048,0.92858365,0.933012702,0.937309854,0.941473796,0.945503262,0.949397023,0.953153894,0.956772729,0.960252427,0.963591927,
0.966790213,0.96984631,0.972759288,0.975528258,0.978152378,0.980630848,0.982962913,0.985147863,0.987185032,0.9890738,0.990813592,
0.992403877,0.99384417,0.995134034,0.996273076,0.997260948,0.998097349,0.998782025,0.999314767,0.999695414,0.999923848,1,0.999923848,
0.999695414,0.999314767,0.998782025,0.998097349,0.997260948,0.996273076,0.995134034,0.99384417,0.992403877,0.990813592,0.9890738,
0.987185032,0.985147863,0.982962913,0.980630848,0.978152378,0.975528258,0.972759288,0.96984631,0.966790213,0.963591927,0.960252427,
0.956772729,0.953153894,0.949397023,0.945503262,0.941473796,0.937309854,0.933012702,0.92858365,0.924024048,0.919335284,0.914518786,
0.909576022,0.904508497,0.899317755,0.894005377,0.888572981,0.883022222,0.87735479,0.871572413,0.865676851,0.8596699,0.853553391,
0.847329185,0.84099918,0.834565303,0.828029514,0.821393805,0.814660196,0.807830738,0.800907512,0.793892626,0.786788218,0.779596452,
0.772319518,0.764959632,0.757519037,0.75,0.74240481,0.734735781,0.72699525,0.719185573,0.711309131,0.703368322,0.695365564,0.687303297,
0.679183975,0.671010072,0.662784077,0.654508497,0.646185852,0.637818678,0.629409523,0.620960948,0.612475527,0.603955845,0.595404498,
0.586824089,0.578217233,0.56958655,0.560934672,0.552264232,0.543577871,0.534878237,0.526167978,0.517449748,0.508726203,0.5,0.491273797,
0.482550252,0.473832022,0.465121763,0.456422129,0.447735768,0.439065328,0.43041345,0.421782767,0.413175911,0.404595502,0.396044155,
0.387524473,0.379039052,0.370590477,0.362181322,0.353814148,0.345491503,0.337215923,0.328989928,0.320816025,0.312696703,0.304634436,
0.296631678,0.288690869,0.280814427,0.27300475,0.265264219,0.25759519,0.25,0.242480963,0.235040368,0.227680482,0.220403548,0.213211782,
0.206107374,0.199092488,0.192169262,0.185339804,0.178606195,0.171970486,0.165434697,0.15900082,0.152670815,0.146446609,0.1403301,
0.134323149,0.128427587,0.12264521,0.116977778,0.111427019,0.105994623,0.100682245,0.095491503,0.090423978,0.085481214,0.080664716,
0.075975952,0.07141635,0.066987298,0.062690146,0.058526204,0.054496738,0.050602977,0.046846106,0.043227271,0.039747573,0.036408073,
0.033209787,0.03015369,0.027240712,0.024471742,0.021847622,0.019369152,0.017037087,0.014852137,0.012814968,0.0109262,0.009186408,
0.007596123,0.00615583,0.004865966,0.003726924,0.002739052,0.001902651,0.001217975,0.000685233,0.000304586,0.0};

void setup () {
     pinMode(RowA, OUTPUT);
     pinMode(RowB, OUTPUT);
     pinMode(RowC, OUTPUT);
     pinMode(RowD, OUTPUT);
     pinMode(OE, OUTPUT);
     pinMode(R1, OUTPUT);
     pinMode(CLK, OUTPUT);
     pinMode(STB, OUTPUT);
     SPI.begin();
     Serial.begin(9600);
     delay(10); 
     randomSeed(analogRead(0));
     clearScreen(screen);
     clearScreen(screenBuffer);
     clearScreen(screenBuffer2);
}    

void loop(){
  for(int i=0;i<2;i++)
    {
      copyScreen(screenBuffer,screen,1);
      copyScreen(spaceInvader,screen,2);
      displayImage(1);
      
      copyScreen(screenBuffer2,screen,1);
      displayImage(15);
      
      if(random(1,4)==1) setPixel(32,random(1,16),1,screenBuffer2);
      moveScreenLeft(1,screenBuffer2); //Rotate left
    }
  //Plot random pixel and shift left
  setPixel(32,random(1,16),1,screenBuffer);
  moveScreenLeft(1,screenBuffer); //Rotate left
  
  //moveScreenRight(2,spaceInvader);
}

// ================[User Methods]==================

// Fill the display screen with zeroes
void clearScreen(byte screenReference[32][4]) {memset(screenReference,0,sizeof(screen));}

// Set state of individual pixel to 0 or 1
void setPixel(int x, int y, boolean state,byte screenReference[32][4])
{
  int realX=x/8;
  int overflowX=(x-1)%8;
  int realY=y-1;
  Serial.println(overflowX);
  if (overflowX==7) realX=realX-1;
  bitWrite(screenReference[realY][realX],(7-overflowX),state);
}

//Swap two variables
void swap(unsigned int * a, unsigned int * b)
{
  unsigned int temp;
  temp=*b;
  *b=*a;
  *a=temp;
}

// Draw a line with Brezenhams Algorithm
void drawLine(unsigned int xStart,  unsigned int yStart, unsigned int xEnd, unsigned int yEnd, int color,byte screenReference[32][4])
{
     boolean steep;
     steep= abs(yEnd - yStart) > abs(xEnd - xStart);
     if (steep)
    {
         swap(&xStart, &yStart);
         swap(&xEnd, &yEnd);
    }
     if (xStart > xEnd)
    {
         swap(&xStart, &xEnd);
         swap(&yStart, &yEnd);
    }
    
     int deltax = xEnd - xStart;
     int deltay = abs(yEnd - yStart);
     int error = 0;
     int ystep;
     int y = yStart;
     int x;

     if (yStart < yEnd) 
       ystep = 1; 
     else 
       ystep = -1;
       
     for (x=xStart; x<=xEnd; x++)
       {
         if (steep) setPixel(y,x,color,screenReference);
         else setPixel(x,y,color,screenReference); 

         error = error + deltay;

         if (2 * error >= deltax)
           {
           y = y + ystep;
           error = error - deltax;
           }
       }
}

// Draw a rectangle
void drawRect(byte xStart,  byte yStart, byte xEnd, byte yEnd,int color,byte screenReference[32][4])
{
  drawLine(xStart,yStart,xEnd,yStart,color,screenReference);
  drawLine(xEnd,yStart,xEnd,yEnd,color,screenReference);
  drawLine(xStart,yStart,xStart,yEnd,color,screenReference);
  drawLine(xStart,yEnd,xEnd,yEnd,color,screenReference);
}

void invertScreenRow(int row,byte screenReference[32][4])
{
  for(int x=0;x<displayWidth;x++){screenReference[row-1][x]=~screenReference[row-1][x];}
}

void invertScreen(byte screenReference[32][4])
{
for(int y=0;y<displayHeight;y++)
  invertScreenRow(y,screenReference);
}

// Copy one screen buffer to another
// METHOD 1:replace(straith memcopy)   METHOD 2: Combine(Logic OR)   
void copyScreen(byte screenReferenceSource[32][4], byte screenReferenceDestination[32][4],int method)
{
  if (method==1)
    memcpy(screenReferenceDestination,screenReferenceSource,sizeof(screen));

  if (method==2)
    for(int y=0;y<displayHeight;y++)
      for(int x=0;x<displayWidth;x++)
          screenReferenceDestination[y][x]=screenReferenceDestination[y][x]|screenReferenceSource[y][x];
}

// Take leftmost column of pixels and put them as the rightmost column
// METHOD 1:Shift     METHOD 2:Rotate
void moveScreenLeft(int method,byte screenReference[32][4])
{
  boolean buffer=0;
  
  for (int y=0 ; y<displayHeight ; y++) 
  {    
    if(method==2)buffer=bitRead(screenReference[y][0],7);
    for(int x=0 ; x<displayWidth-1 ; x++) 
      screenReference[y][x] = screenReference[y][x]<<1 | screenReference[y][x+1]>>7;       
    screenReference[y][displayWidth-1] = screenReference[y][displayWidth-1]<<1 | buffer; 
  }
}

void moveScreenRight(int method,byte screenReference[32][4])
{
  boolean buffer=0;
  
  for (int y=0 ; y<displayHeight ; y++) 
  {    
    if(method==2)buffer=bitRead(screenReference[y][displayWidth-1],0);  
    
    for(int x=displayWidth-1 ; x>0 ; x--) 
      screenReference[y][x] = screenReference[y][x]>>1 | screenReference[y][x-1]<<7; 
      
    screenReference[y][0] = screenReference[y][0]>>1 | buffer; 
  }
}

// Send screen[][] to physical display for x milliseconds
// Refreshing the display actually takes only 850 microseconds. 
// Adding a delay of 150 microseconds takes it to 1ms. 
void displayImage(int milliseconds)
{
  for (int i=0;i<milliseconds;i++)
  {
    refreshDisplay();
    delayMicroseconds(150);
  }
}

// ================[System Methods]==================
// Send 16x32 screen to display once
void refreshDisplay()
{
  for(int row=0;row<displayHeight;row++)
  {
    for(int col=0;col<displayWidth;col++) 
      SPI.transfer(~(screen[row][col]));
    writeRow(row);
  }  
}

// After sending 32 bits with STI.transfer, call this method to update
// one row on the display. Row is indicated by "row" integer
void writeRow(int row){
    digitalWrite(OE,HIGH);
    hc138sacn(row);
    digitalWrite(STB,LOW);
    digitalWrite(STB,HIGH);
    //delayMicroseconds(500);
    digitalWrite(OE,LOW);
    //delayMicroseconds(500); 
}

void hc138sacn(byte r){
  digitalWrite(RowA,(r & 0x01));
  digitalWrite(RowB,(r & 0x02));
  digitalWrite(RowC,(r & 0x04));
  digitalWrite(RowD,(r & 0x08));
  
}  

