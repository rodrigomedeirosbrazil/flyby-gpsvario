#include <Arduino.h>
#include "defines.h"
#include "helpers/helpers.h"
#include "Screen/Screen.h"
#include "FlightCpu/FlightCpu.h"
#include "Webserver/Webserver.h"
#include "globals.h"

void setup(void) {
  startSound();

  // Start webserver for 60 seconds
  webserver.begin();

  delay(POWER_ON_DELAY);

  barometer.begin();
  gps.begin();
  screen.begin();
}

void loop(void) {
  // Process webserver if still active
  if (webserver.isActive()) {
    webserver.tick();
  }
  
  flightCpu.tick();
}
