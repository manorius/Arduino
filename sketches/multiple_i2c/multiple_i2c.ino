#include <Wire.h>

int address_sensor1= 72; //binary equivalent is 1001000

int address_sensor2= 73; //binary equivalent is 1001001

#define PN532_I2C_ADDRESS                   (0x48 >> 1)
#define PN532_I2C_READBIT                   (0x01)
#define PN532_I2C_READYTIMEOUT              (20)

void setup(){

Serial.begin(9600); //this creates the Serial Monitor
Wire.begin(); //this creates a Wire object
}

void loop(){
  Serial.print("looped");
Wire.beginTransmission(address_sensor1); //Send a request to begin communication with the device at the specified address

Wire.write(0); //Sends a bit asking for register 0, the data register of the TC74 sensor

Wire.endTransmission(); //this ends transmission of data from the arduino to the temperature sensor

//this now reads the temperature from the TC74 sensor
Wire.requestFrom(PN532_I2C_ADDRESS, 12);//this requests 1 byte from the specified address
int av = Wire.available();
Serial.print("available: ");
Serial.print(av);

while(Wire.available() == 0);
int readInfo= Wire.read();

Serial.print("Read info: ");
Serial.print(readInfo);

delay(2000);
} 

