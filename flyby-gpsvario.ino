#include "src/defines.h"
#include "src/Screen/Screen.h"
#include "src/Variometer/Variometer.h"
#include "src/Beep/Beep.h"
#include "src/Gps/Gps.h"

Variometer variometer;
Gps gps;
Beep beep(SPEAKER_PIN);
Screen screen(&variometer, &gps);

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  screen.begin();
}

void loop(void) {
  variometer.tick();
  beep.tick(variometer.getVario());
  gps.tick();

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
