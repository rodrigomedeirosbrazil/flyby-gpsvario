#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>

void noTone(uint8_t pin, uint8_t channel = 0);
void tone(uint8_t pin, unsigned int frequency, unsigned long duration, uint8_t channel = 0);
void startSound();
void adjustTimezone(int timezone, int *year, byte *month, byte *day, byte *hour);

#endif
