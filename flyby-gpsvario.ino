#include <U8g2lib.h>
#include "src/defines.h"
#include "src/Screen/Screen.h"

#ifndef DEMO
  #include "src/Variometer/Variometer.h"
  #include "src/Beep/Beep.h"
#endif

Screen screen;

#ifndef DEMO
  Variometer variometer;
  Beep beep(SPEAKER_PIN);
#endif

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  screen.begin();
}

void loop(void) {
  #ifndef DEMO
    variometer.tick();
    beep.tick(variometer.getVario());

    screen.setDegree(0);
    screen.setAltitude(0);
    screen.setSpeed(0);
    screen.setVario(variometer.getVario());
  #endif

  screen.draw();
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
