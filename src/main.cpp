#include <Arduino.h>
#include "defines.h"
#include "helpers/helpers.h"
#include "Screen/Screen.h"
#include "FlightCpu/FlightCpu.h"
#include "globals.h"

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  barometer.begin();
  gps.begin();
  screen.begin();
}

void loop(void) {
  flightCpu.tick();
}
