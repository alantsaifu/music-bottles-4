#include <Adafruit_NeoPixel.h>

#define NeoPixelPin 10

#include "neopixelbottlesthirds.h"


//NOTICE! Pins 2-7 are 'hard-coded' in a number of places in the code, do not change this!
#define CO_CAP ((PIND & 4) == 4)
#define CO_BOT ((PIND & 8) == 8)
#define ST_CAP ((PIND & 16) == 16)
#define ST_BOT ((PIND & 32) == 32)
#define SP_CAP ((PIND & 64) == 64)
#define SP_BOT ((PIND & 128) == 128)

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);

  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  lights.begin();
 //  lights.RainbowCycle(100);
 // Serial.begin(115200);
}

void loop() {
  lights.Update();
 /* 
  Serial.print();
  Serial.print((PIND & 8) == 8);
  Serial.print((PIND & 16) == 16);
  Serial.print((PIND & 32) == 32);
  Serial.print((PIND & 64) == 64);
  Serial.println((PIND & 128) == 128);
 */
  
  int g = (CO_BOT) ? ((!CO_CAP) ? 255 : 90) : 30;
  int r = (ST_BOT) ? ((!ST_CAP) ? 255 : 90) : 30;
  int b = (SP_BOT) ? ((!SP_CAP) ? 255 : 90) : 30;

 
  //Serial.println(r);
  if (!lightsRunning) {
    /*
    if (!bottleStates.cone.bottleOn && !bottleStates.straight.bottleOn && !bottleStates.sphere.bottleOn) {
      fadeTo(C_WHITE);
    } else if (bottleStates.cone.bottleOn && bottleStates.straight.bottleOn && bottleStates.sphere.bottleOn) {
      fadeTo(C_DARKBLUE);     
    } else if (bottleStates.cone.bottleOn && bottleStates.straight.bottleOn && bottleStates.sphere.bottleOn) {
    
    }*/
    fadeTo(lights.Color(g,r,b));
  }
}

void fadeTo(uint32_t c) {
//    static uint32_t lastColor = lights.Color(127, 127, 127);
//      lights.Fade(lastColor, c, 30, 5);
//      lastColor = c;    
   nextLight = c;
   if (!lightsRunning) {
     lights.Fade(lights.Color2, c, 90, 5);
   } 
   lightsRunning = true;
}

