#include <Wire.h>

unsigned short num;
short raw_data[5]={
  0, };
short sub_os_data[5];
signed short ret;
short act_os_d[4]={
  0x03FF, 0x03FF, 0x03FF, 0x03FF};

void I2C_write(unsigned char add,unsigned char reg,unsigned char data) {
  Wire.beginTransmission(add);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission(1);  
}

void setup()
{
  ////////IO Init
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(115200);  // start serial for output

  ///////Sensor Init
  Wire.beginTransmission(0x39);
  Wire.write(0x00);
  Wire.write(0xc0);
  Wire.write(0x62);
  Wire.write(0x01);
  Wire.endTransmission();


}

void loop()
{
  ////Getting Gesture Data from Sensor
  unsigned char i;
  unsigned short GD0=0,GD1=0,GD2=0,GD3=0,GD4=0;
  Wire.beginTransmission(0x39);
  Wire.write(0x10);
  Wire.endTransmission(0);
  Wire.requestFrom(0x39, 10);    // request 10 bytes from slave device

  i=0;
  while(Wire.available())
  { 
        unsigned char c = Wire.read(); // receive a byte as character
        

        
    switch (i) {
    case 0:
      GD0=c;
      break;  
    case 1:
      GD0+=(((unsigned short)c)<<8);
      break; 
    case 2:
      GD1=c;
      break; 
    case 3:
      GD1+=(((unsigned short)c)<<8);
      break; 
    case 4:
      GD2=c;
      break; 
    case 5:
      GD2+=(((unsigned short)c)<<8);
      break; 
    case 6:
      GD3=c;
      break; 
    case 7:
      GD3+=(((unsigned short)c)<<8);
      break; 
    case 8:
      GD4=c;
      break; 
    case 9:
      GD4+=(((unsigned short)c)<<8);
      break; 
    }
    i++;
  }

  raw_data[0]=GD0;
  raw_data[1]=GD1;
  raw_data[2]=GD2;
  raw_data[3]=GD3;

 
  if( (raw_data[0] & 0x8000) || (raw_data[1] & 0x8000) ||
    (raw_data[2] & 0x8000) || (raw_data[3] & 0x8000) ){
    for(num=0;num<4;num++){
      raw_data[num] = 0;
    }
    }

    
  Serial.println(raw_data[0]);
  
    delay(50);
}
