#include "leds.h"

CRGB leds[NUM_LEDS];

void setup_leds() {

  FastLED.addLeds<WS2812B, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);

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


void led(int nb, String mod, int couleur) {
  if (mod == "rgb") {
    for (int i = 0; i < nb; i++) {
      leds[i] = CRGB(couleur);;
    }
    FastLED.show();
  }

  else if (mod == "hsv") {
    for (int i = 0; i < nb; i++) {
      //leds[i] = CHSV(couleur);;
    }
    FastLED.show();
  }

  else {
    Serial.println("Frero t'a marque dla merde");
  }
}

void loop_leds() {

}
