#include <Arduino.h>

#include "config.h"
#include "helpers/helpers.h"
#include "FlightCpu/FlightCpu.h"

FlightCpu *flightCpu;

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  flightCpu = new FlightCpu();
}

void loop(void) {
  flightCpu->tick();
}
