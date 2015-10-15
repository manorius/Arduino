#include "LEDMatrix.h"

#define WIDTH   32
#define HEIGHT  16

LEDMatrix matrix(4, 5, 6, 7, 8, 9, 10, 11);	

uint8_t displaybuf[WIDTH *HEIGHT / 8]; 			// Display Buffer

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

    matrix.begin(displaybuf, WIDTH, HEIGHT);
}

int dir = 0;

void loop() {
  // put your main code here, to run repeatedly: 
  static uint32_t lastCountTime = 0;
    static uint8_t x = 0;
    static uint8_t y = -1;
     static uint8_t onoff = 0;
     
    matrix.scan();
    if ((millis() - lastCountTime) > 100) {
      lastCountTime = millis();
      
      if(x==0)
     {
       y = (y + 1) & 0x0F;
       //onoff = (onoff+1)%2;
       dir = (dir+1)%2;
     }
     
      matrix.drawPoint(x, y, 1);
     if(dir==0) x = (x+1)%32;
     else x = (x-1)%32;
      
//        lastCountTime = millis();
        Serial.println(dir);
        Serial.print(x);Serial.print("-");Serial.print(y);
//        Serial.println((count + 1));
//        Serial.println((count + 1) & 0x0F);
//        Serial.println("----");
//        count = (count + 1) & 0x0F;
    }
    
}
