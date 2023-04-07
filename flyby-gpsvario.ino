#include "src/defines.h"
#include "src/helpers/helpers.h"
#include "src/Screen/Screen.h"
#include "src/Variometer/Variometer.h"
#include "src/Beep/Beep.h"
#include "src/Gps/Gps.h"

Variometer *variometer;
Gps *gps;
Beep *beep;
Screen *screen;
unsigned long smallerVdop = 9999;

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  variometer = new Variometer();
  gps = new Gps();
  beep = new Beep(SPEAKER_PIN);
  screen = new Screen(variometer, gps);

  screen->begin();
}

void loop(void) {
  variometer->tick();
  beep->tick(variometer->getVario());
  gps->tick();
  autoAdjustQNH();

  screen->draw();
}

void autoAdjustQNH() {
  if (! gps->isAvailable() || smallerVdop <= gps->getVdop()) {
    return;
  }

  smallerVdop = gps->getVdop();
  variometer->setQnhByAltitude(gps->getAltitude());
  coinSound();
}