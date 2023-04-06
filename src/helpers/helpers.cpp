#include "helpers.h"
#include "../defines.h"

void startSound()
{
  tone(SPEAKER_PIN, 300, 500);
  delay(500);
  tone(SPEAKER_PIN, 400, 500);
  delay(500);
  tone(SPEAKER_PIN, 500, 500);
  delay(500);
}

void notificationSound()
{
    tone(SPEAKER_PIN,1319,125);
    delay(130);
    tone(SPEAKER_PIN,1568,125);
    delay(130);
    tone(SPEAKER_PIN,2637,125);
    delay(130);
    tone(SPEAKER_PIN,2093,125);
    delay(130);
    tone(SPEAKER_PIN,2349,125);
    delay(130);
    tone(SPEAKER_PIN,3136,125);
    delay(125);
    noTone(SPEAKER_PIN);
}

void adjustTimezone(int timezone, int *year, byte *month, byte *day, byte *hour)
{
    *hour += timezone;
    if (*hour < 0) {
        *hour += 24;
        if (day) *day -= 1;
        if (month) *month -= 1;
        if (year) *year -= 1;
    }
    if (*hour > 23) {
        *hour -= 24;
        if (day) *day += 1;
        if (month) *month += 1;
        if (year) *year += 1;
    }
}