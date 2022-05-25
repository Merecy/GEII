#include "leds.h"
#include <FastLED.h>

#define DATA_PIN D8
#define CLOCK_PIN 13


CRGB leds[NUM_LEDS];
CRGB cyan;
CHSV rainbow;

int h = 360;

void setup_leds() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  couleur();
}

void ledun() {
  static int i;
  if (i <= NUM_LEDS)
    leds[i] = cyan;

  if (i > NUM_LEDS && i <= NUM_LEDS*2)
    leds[i - (NUM_LEDS+1)] = CRGB::Red;

  i++;
  if (i > NUM_LEDS*2)i = 0;

  FastLED.show();
  delay(50);
}

void testhsv() {
  if ( rainbow.hue > 0 ) {
    rainbow.hue -= 1 ; // la teinte diminue vers le rouge h=0
  }
  else {
    rainbow.hue = 255 * (h / 360.0) ;
  }
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = rainbow;
  }
  FastLED.show();
}

void lumiere(float x) {
  rainbow.hue = 255 * map(x, 10, 220, 230, 360) / 360.0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = rainbow;
  }
  FastLED.show();
}

void couleur() {
  cyan.red = 51;
  cyan.green = 255;
  cyan.blue = 240;

  rainbow.value = 255;
  rainbow.sat = 255;
  rainbow.hue = 255 * (h / 360.0);
}
