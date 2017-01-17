#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <Wire.h>

unsigned short num;
short raw_data[5]={
  0, };
short sub_os_data[5];
signed short ret;
short act_os_d[4]={
  0x03FF, 0x03FF, 0x03FF, 0x03FF};

#define PIN 12

#define NUM_LEDS 11

#define BRIGHTNESS 50

int brightness = 0;
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;       

const long fadeInterval = 50;           // interval at which to blink (milliseconds)
const long turnOffInterval = 5000;
boolean ledState = false;
boolean fadeState = false;
boolean runningFade = false;
int R = 255;
int G = 255;
int B = 255;
int mode = 0;
float filterVal = 0.1;       // this determines smoothness  - .0001 is max  1 is off (no smoothing)
float smoothedVal;     // this holds the last loop value just use a unique variable for every different sensor that needs smoothing

float smoothedVal2;   // this would be the buffer value for another sensor if you needed to smooth two different sensors - not used in this sketch


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

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

strip.setBrightness(0);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(R, G, B));
    strip.show();
}

}

int ledNum = 0;


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

  Serial.println(raw_data[0]);

  if(/*raw_data[0]>14*/false)
  {

    if(!runningFade) fadeState = true;
  }
  
  if( (raw_data[0] & 0x8000) || (raw_data[1] & 0x8000) ||
    (raw_data[2] & 0x8000) || (raw_data[3] & 0x8000) ){
    for(num=0;num<4;num++){
      raw_data[num] = 0;
    }
  }





// fadeState true  => fade in
// fadeState false => fade out 
if(mode == 0){
  if(ledState!=fadeState)
  {
    runningFade = true;
    fade(fadeState);
    //Serial.println("TURN ON");

  }
  else if(ledState == true && fadeState==true)
  {
    
   
    
    // START COUNTDOWN FOR TURNING OFF
    unsigned long currentMillis = millis();
//     Serial.println(currentMillis);
//    Serial.println("-----------");
//    Serial.println(previousMillis);
    if (currentMillis - previousMillis >= turnOffInterval) {
  
//      Serial.println("start - ledState");
//Serial.println(ledState);
//Serial.println("start - fadeState");
//Serial.println(fadeState);
      //Serial.println("TURN OFF");
      previousMillis = 0;
      fadeState = false;
    }
  }
  else
  {
    runningFade = false;
  }
}
else if(mode == 1)
{
  distanceFade();
  //Serial.println(human_sensor.getRawValue());
  //long br = map((long) human_sensor.getRawValue(),700,730,0,80);
  //Serial.println(br);
  //delay(50);
//for(uint16_t i=0; i<strip.numPixels(); i++) {
//    strip.setPixelColor(i, strip.Color(255, 255, 255));
//}
//  strip.setBrightness(brightness);
//  strip.show();
  
}

}


void distanceFade()
{
  R = random(255);
  G = random(255);
  B = random(255);
for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(R, G, B));
}
  strip.setBrightness(brightness);
  strip.show();
  mode = 0;
// unsigned long currentMillis = millis();
//
//
//
//if (currentMillis - previousMillis >= 50)
//{
//
//   smoothedVal =  smooth((int) human_sensor.getRawValue(), filterVal, smoothedVal);
// Serial.println(smoothedVal);
////  previousMillis = currentMillis;
////  //Serial.println(human_sensor.getRawValue());
////  long br = map((long) human_sensor.getRawValue(),700,730,0,80);
////  Serial.println(br);
////  for(uint16_t i=0; i<strip.numPixels(); i++) {
////    strip.setPixelColor(i, strip.Color(255, 255, 255));
////}
////  strip.setBrightness(br);
////  strip.show();
//  }

}

void fade(boolean state)
{
 
 unsigned long currentMillis = millis();



if (currentMillis - previousMillis >= fadeInterval) {
  if(brightness<=BRIGHTNESS && brightness>=0){
  previousMillis = currentMillis;
  
  brightness = ( state == true )? brightness+1 : brightness-1;
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(R, G, B));
}
  strip.setBrightness(brightness);
  strip.show();
//Serial.println("brightness");
//Serial.println(brightness);
}
else
{
  

  //previousMillis = 0;
  brightness = ( state == true )? BRIGHTNESS : 0;
  ledState = fadeState;
//  Serial.println("end - ledState");
//Serial.println(ledState);
//Serial.println("end - fadeState");
//Serial.println(fadeState);
}
}

}
