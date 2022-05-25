#ifndef CAPTEURS_H
#define CAPTEURS_H
#define capteur 0x23
#include <Wire.h>
void setup_capteurs();
void i2cWrite8(uint8_t data);
void loop_capteurs();
uint16_t lumina();
#endif
