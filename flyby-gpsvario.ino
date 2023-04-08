#include "src/defines.h"
#include "src/helpers/helpers.h"
#include "src/Screen/Screen.h"
#include "src/Variometer/Variometer.h"
#include "src/Beep/Beep.h"
#include "src/Gps/Gps.h"
#include "src/FlightCpu/FlightCpu.h"

Variometer *variometer;
Gps *gps;
Beep *beep;
Screen *screen;
FlightCpu *flightCpu;

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  variometer = new Variometer();
  gps = new Gps();
  beep = new Beep(SPEAKER_PIN);
  screen = new Screen(variometer, gps);
  flightCpu = new FlightCpu(variometer, gps, beep, screen);

  screen->begin();
}

void loop(void) {
  variometer->tick();
  beep->tick(variometer->getVario());
  gps->tick();
  flightCpu->tick();

  screen->draw();
}
