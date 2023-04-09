#include <time.h>
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

void oneUpSound()
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

void coinSound()
{
    tone(SPEAKER_PIN, 988, 100);
    delay(100);
    tone(SPEAKER_PIN, 1319, 500);
    delay(800);
    noTone(SPEAKER_PIN);
}
  
void fireballSound()
{
    tone(SPEAKER_PIN,196,35);
    delay(35);
    tone(SPEAKER_PIN,784,35);
    delay(35);
    tone(SPEAKER_PIN,1568,35);
    delay(35);
    noTone(SPEAKER_PIN);
}

// void gameoverSound()
// {
//   NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
//   NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
//   NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  
// }

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

unsigned long convertDateAndTimeEpochTime(
    unsigned long date, // format ddmmyy
    unsigned long time // format hhmmsscc
) {
    struct tm timestamp;
    timestamp.tm_mday = date / 10000;
    timestamp.tm_mon = ((date - timestamp.tm_mday * 10000) / 100) - 1;
    timestamp.tm_year = date - timestamp.tm_mday * 10000 - (timestamp.tm_mon + 1) * 100 + 2000 - 1900;
    timestamp.tm_hour = time / 1000000;
    timestamp.tm_min = (time - timestamp.tm_hour * 1000000) / 10000;
    timestamp.tm_sec = (time - timestamp.tm_hour * 1000000 - timestamp.tm_min * 10000) / 100;
    
    return mktime(&timestamp);
}
