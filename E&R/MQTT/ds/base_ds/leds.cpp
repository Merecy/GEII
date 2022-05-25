#include "leds.h"

CRGB leds[NUM_LEDS];

void setup_leds() {

  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  
  FastLED.setBrightness(32);


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
