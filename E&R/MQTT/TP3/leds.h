#ifndef LEDS_H
#define LEDS_H
void setup_leds();
void loop_leds();
void traitementLed(int numLED, int color);
#endif

#define DATA_PIN D8
#define NUM_LEDS 8
#define BRIGHTNESS  64
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
