#include "src/defines.h"
#include "src/helpers/helpers.h"
#include "src/FlightCpu/FlightCpu.h"

FlightCpu *flightCpu;

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  flightCpu = new FlightCpu();
}

void loop(void) {
  flightCpu->tick();
}
