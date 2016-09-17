#include <PN532_HSU.h>
#include <PN532.h>
#include <NfcAdapter.h>

//#include <SoftwareSerial.h>

//SoftwareSerial Serial1(10, 11); // RX, TX

PN532_HSU pn532hsu(Serial);
PN532 nfc(pn532hsu);

void setup(void)
{
   Serial.begin(9600);
    //nfc.begin();
    //...
}

void loop()
{


}

