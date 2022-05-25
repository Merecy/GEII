#ifndef LEDS_H
#define LEDS_H
#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>
void setup_leds();
void loop_leds();
void led(int nb, String mod, int couleur);
#define NUM_LEDS 8
#define DATA_PIN 15
#define COLOR_ORDER GRB
//GRB
#endif
