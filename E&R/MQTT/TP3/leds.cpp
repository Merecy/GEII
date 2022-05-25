#include <FastLED.h>
#include "leds.h"

CRGB leds[NUM_LEDS];
CHSV hsv;

void setup_leds() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}

void loop_leds() {
}

void traitementLed(int numLED, int color) {
  Serial.println(numLED);
  leds[numLED] = CRGB(color);
  FastLED.show();
}
