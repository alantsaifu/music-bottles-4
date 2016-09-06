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

 // Serial.begin(115200);
 // Serial.print("hello");
}

void loop() {
  bool bottleStates[3] = { CO_BOT,ST_BOT,SP_BOT };
  bool capStates[3] = {CO_CAP, ST_CAP, SP_CAP};
  lights.setBottleStates( bottleStates , capStates );
  lights.Update();
   
}

