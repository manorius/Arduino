#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif


#include <RBD_Capacitance.h> // https://github.com/alextaujenis/RBD_Capacitance
#include <RBD_Threshold.h>   // https://github.com/alextaujenis/RBD_Threshold
#include <RBD_HumanSensor.h> // https://github.com/alextaujenis/RBD_HumanSensor

RBD::HumanSensor human_sensor(2, 3); // send, receive pin

#define PIN 6

#define NUM_LEDS 12

#define BRIGHTNESS 255

int brightness = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;       

// constants won't change :
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


void setup() {
  Serial.begin(115200);
  human_sensor.setNearValue(715);
  human_sensor.setTouchValue(1900);
  human_sensor.setPickupValue(1000);
  strip.setBrightness(0);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(R, G, B));
    strip.show();
}
}
int ledNum = 0;
void loop() {
  
  human_sensor.update();
  if(human_sensor.onGone()) {
    Serial.print("0. GONE   ");
  }
  else if(human_sensor.onNear()) {
    Serial.print("1. NEAR   ");
      if(!runningFade) fadeState = true;
  }
  else if(human_sensor.onTouch()) {
    Serial.print("2. TOUCH  ");
    
  }
  else if(human_sensor.onPickup()) {
    Serial.print("3. PICKUP ");
    mode = (mode==0)? 1:0;
    Serial.println(mode);
  }

  if(human_sensor.onRawValueChange()) {
    //Serial.println(human_sensor.getRawValue());
  }
 
//Serial.println(brightness);
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


