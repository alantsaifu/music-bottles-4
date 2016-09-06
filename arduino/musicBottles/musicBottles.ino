#include <Adafruit_NeoPixel.h>
#include "neopixelbottlesthirds.h"

#define NeoPixelPin 10

//NOTICE! Pins 2-7 are 'hard-coded' in a number of places in the code, do not change this!
#define CO_CAP ((PIND & 4) != 4)
#define CO_BOT ((PIND & 8) == 8)
#define ST_CAP ((PIND & 16) != 16)
#define ST_BOT ((PIND & 32) == 32)
#define SP_CAP ((PIND & 64) != 64)
#define SP_BOT ((PIND & 128) == 128)

BottleNeoPatterns lights(108, NeoPixelPin, NEO_RGBW + NEO_KHZ800, 75, 2);

void setup() {
  for (int i=2; i<=7; i++) { pinMode(i, INPUT_PULLUP); }
  lights.begin();
}

void loop() {
  //handle states
  bool bottleStates[3] = { CO_BOT, ST_BOT, SP_BOT };
  bool capStates[3] = {CO_CAP, ST_CAP, SP_CAP};
  lights.setBottleStates( bottleStates , capStates );

  //handle lights
  lights.Update();
}
