#include "leds.h"

CRGB leds[NUM_LEDS];

void setup_leds() {

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);

  FastLED.setBrightness(16);


  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Red;

  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Green;

  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;

  }
  FastLED.show();
  delay(500);
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    delay(100);
    FastLED.show();
  }
}

void loop_leds() {

}

void stateled(String state) {
  if (state == "on") {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
      leds[NUM_LEDS-i] = CRGB::Red;
      delay(100);
      FastLED.show();
    }
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      leds[NUM_LEDS-i] = CRGB::Black;
      delay(100);
      FastLED.show();
    }
  }
}

void stateRGB(String state, int r, int g, int b){
    if (state == "on") {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Red;
      leds[NUM_LEDS-i] = CRGB::Red;
      delay(100);
      FastLED.show();
    }
  }
  else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      leds[NUM_LEDS-i] = CRGB::Black;
      delay(100);
      FastLED.show();
    }
  }
}
}
