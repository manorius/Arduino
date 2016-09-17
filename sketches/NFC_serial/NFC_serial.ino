/* 

PN532 reads the tag by Arduino mega/Leonardo
command list:

#wake up reader
send: 55 55 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ff 03 fd d4 14 01 17 00
return: 00 00 FF 00 FF 00 00 00 FF 02 FE D5 15 16 00

#get firmware
send: 00 00 FF 02 FE D4 02 2A 00
return: 00 00 FF 00 FF 00 00 00 F F 06 FA D5 03 32 01 06 07 E8 00

#read the tag
send: 00 00 FF 04 FC D4 4A 01 00 E1 00
return: 00 00 FF 00 FF 00 00 00 FF 0C F4 D5 4B 01 01 00 04 08 04 XX XX XX XX 5A 00
XX is tag.

*/

const unsigned char wake[24]={0x55,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0x03,0xfd,0xd4,0x14,0x01,0x17,0x00};//wake up NFC module
const unsigned char firmware[9]={0x00,0x00,0xFF,0x02,0xFE,0xD4,0x02,0x2A,0x00};//
const unsigned char tag[11]={0x00,0x00,0xFF,0x04,0xFC,0xD4,0x4A,0x01,0x00,0xE1,0x00};//detecting tag command

unsigned char receive_ACK[25];//Command receiving buffer
int inByte = 0;               //incoming serial byte buffer

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#define print1Byte(args) Serial1.write(args)
#define print1lnByte(args)  Serial1.write(args),Serial1.println()
#else
#include "WProgram.h"
#define print1Byte(args) Serial1.print(args,BYTE)
#define print1lnByte(args)  Serial1.println(args,BYTE)
#endif
#include <SoftwareSerial.h>
SoftwareSerial Serial1(10,11); // RX, TX

void setup()
{
  Serial.begin(9600); // open serial锛宻et Baund rate 9600 bps
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial1.begin(115200);
  wake_card();
  delay(100);
  array_ACK(15);
  delay(100);
  dsplay(15);
  

}

void loop()
{
  //Serial.print(Serial1.available());
 read_tag();
      delay(10);
      array_ACK(25);
     delay(10);
  dsplay(25);
  delay(10);
  Serial.print("\n\r");
  
//   if (Serial1.available() > 0) 
//   {
//    // get incoming byte:
//    inByte = Serial1.read();
//    if (inByte=='r')
//    {   
//      read_tag();
//      delay(100);
//      array_ACK(25);
//      delay(100);
//      dsplay(25);
//    }
//    else if (inByte=='v')
//    {
//       firmware_version();
//       delay(100);
//       array_ACK(19);
//       delay(100);
//       dsplay(19);
//    }
//    
//   }
}

void UART1_Send_Byte(unsigned char command_data)
{
  //Serial1.print(command_data);
  print1Byte(command_data);// command send to device
  #if defined(ARDUINO) && ARDUINO >= 100
    Serial1.flush();// complete the transmission of outgoing serial data 
    #endif
} 

void UART_Send_Byte(unsigned char command_data)//, unsigned charBYTE
{
  Serial.print(command_data,HEX);
  
} 


void array_ACK(unsigned char temp)
{
    for(unsigned char i=0;i<temp;i++)                                           
    {
       receive_ACK[i]= Serial1.read();
       delay(20);
    }
}

void wake_card(void)
{
    unsigned char i;
    for(i=0;i<24;i++) //send command
   UART1_Send_Byte(wake[i]);
}

void firmware_version(void)
{
    unsigned char i;
    for(i=0;i<9;i++) //send command
    UART1_Send_Byte(firmware[i]);
}

void read_tag(void)
{
    unsigned char i;
    for(i=0;i<11;i++) //send command
    UART1_Send_Byte(tag[i]);
}

void dsplay(unsigned char tem)
{
    unsigned char i;
    for(i=0;i<tem;i++) //send command
    UART_Send_Byte(receive_ACK[i]);
    
}

