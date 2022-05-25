#ifndef LEDS_H
#define LEDS_H
void setup_leds();
void ledun();
void testhsv();
void couleur();
void lumiere(float x);
#endif

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define NUM_LEDS 8
#define BRIGHTNESS  16
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
