#include "src/defines.h"
#include "src/Screen/Screen.h"
#include "src/Variometer/Variometer.h"
#include "src/Beep/Beep.h"

Variometer variometer;
Beep beep(SPEAKER_PIN);
Screen screen(&variometer);

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  screen.begin();
}

void loop(void) {
  #ifndef DEMO
    variometer.tick();
    beep.tick(variometer.getVario());
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
