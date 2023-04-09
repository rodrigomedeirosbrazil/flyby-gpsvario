#ifndef HELPERS_H
#define HELPERS_H

#include <Arduino.h>

void startSound();
void oneUpSound();
void coinSound();
void fireballSound();

unsigned long convertDateAndTimeEpochTime(
    unsigned long date, // format ddmmyy
    unsigned long time // format hhmmsscc
);

#endif
