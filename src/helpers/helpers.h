#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>

void startSound();
void oneUpSound();
void coinSound();
void fireballSound();
void adjustTimezone(int timezone, int *year, byte *month, byte *day, byte *hour);

#endif
