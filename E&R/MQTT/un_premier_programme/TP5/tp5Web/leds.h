#ifndef LEDS_H
#define LEDS_H
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
void setup_leds();
void loop_leds();
void stateled(String state);
void stateRGB(String state, int r, int g, int b);
#define NUM_LEDS 64
#define DATA_PIN 15
#endif
