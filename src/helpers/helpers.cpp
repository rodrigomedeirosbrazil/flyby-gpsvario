#include "helpers.h"
#include "../defines.h"

void noTone(uint8_t pin, uint8_t channel)
{
    ledcDetachPin(pin);
    ledcWrite(channel, 0);
}

void tone(uint8_t pin, unsigned int frequency, unsigned long duration, uint8_t channel)
{
    if (ledcRead(channel)) {
        return;
    }
    ledcAttachPin(pin, channel);
    ledcWriteTone(channel, frequency);
    if (duration) {
        delay(duration);
        noTone(pin, channel);
    }    
}

void startSound()
{
  tone(SPEAKER_PIN, 300, 500);
  delay(500);
  tone(SPEAKER_PIN, 400, 500);
  delay(500);
  tone(SPEAKER_PIN, 500, 500);
  delay(500);
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