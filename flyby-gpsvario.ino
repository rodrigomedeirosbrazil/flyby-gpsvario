#include "src/defines.h"
#include "src/helpers/helpers.h"
#include "src/Screen/Screen.h"
#include "src/Variometer/Variometer.h"
#include "src/Beep/Beep.h"
#include "src/Gps/Gps.h"

Variometer variometer;
Gps gps;
Beep beep(SPEAKER_PIN);
Screen screen(&variometer, &gps);

void setup(void) {
  // startSound();
  Serial.begin(115200);

  delay(POWER_ON_DELAY);

  screen.begin();
}

void loop(void) {
  variometer.tick();
  beep.tick(variometer.getVario());
  gps.tick();

  screen.draw();
}
