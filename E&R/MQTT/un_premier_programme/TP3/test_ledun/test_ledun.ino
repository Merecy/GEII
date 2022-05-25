#include <FastLED.h>


#define FASTLED_ESP8266_RAW_PIN_ORDER
#define NUM_LEDS 8
#define BRIGHTNESS  16
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define DATA_PIN D8
#define CLOCK_PIN 13

CRGB leds[NUM_LEDS];
CRGB cyan;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  couleur();

}

void loop() {
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


void couleur() {
  cyan.red = 51;
  cyan.green = 255;
  cyan.blue = 240;
}
