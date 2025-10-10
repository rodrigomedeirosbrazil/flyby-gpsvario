#include <Arduino.h>
#include "defines.h"
#include "helpers/helpers.h"
#include "globals.h"

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  screen.begin();
}

void loop(void) {
  flightCpu.tick();
}
