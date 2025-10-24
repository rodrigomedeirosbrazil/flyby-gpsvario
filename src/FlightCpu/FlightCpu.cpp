#include "FlightCpu.h"
#include "../globals.h"
#include "../Barometer/Barometer.h"
#include "../Variometer/Variometer.h"
#include "../Beep/Beep.h"
#include "../Gps/Gps.h"
#include "../Wind/Wind.h"
#include "../Screen/Screen.h"
#include "../Thermal/Thermal.h"

FlightCpu::FlightCpu() {
}

void FlightCpu::tick() {
    if (barometer.isAvailable()) {
      variometer.tick(barometer.getPressure(), millis());
    }

    if (inFlight) {
      beep.tick(variometer.getVario());
    }

    gps.tick();
    screen.draw();

    bySecondTask();
}

void FlightCpu::bySecondTask() {
    if (millis() - lastTimeBySecondTask < 1000) {
        return;
    }
    lastTimeBySecondTask = millis();

    autoAdjustQNH();
    checkInFlight();
    if (inFlight) {
      wind.storeSpeed(gps.getHeading(), gps.getSpeed(), millis());
      thermal.tick();
    }
}

void FlightCpu::autoAdjustQNH() {
  if (! gps.isReliable() || smallerVdop <= gps.getVdop()) {
    return;
  }

  smallerVdop = gps.getVdop();
  variometer.setQnhByAltitude(gps.getAltitude());
}

void FlightCpu::checkInFlight() {
  if (! inFlight && gps.getSpeed() > TAKEOFF_SPEED && inFlightCounter == 4) {
    inFlight = true;
    inFlightCounter = 0;
    startFlightTime = millis();
    oneUpSound();
  } else if (! inFlight && gps.getSpeed() > TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter++;
  } else if (! inFlight && gps.getSpeed() < TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter = 0;
  } else if (inFlight && gps.getSpeed() < TAKEOFF_SPEED && inFlightCounter == 4) {
    inFlight = false;
    inFlightCounter = 0;
    fireballSound();
    fireballSound();
    fireballSound();
  } else if (inFlight && gps.getSpeed() < TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter++;
  } else if (inFlight && gps.getSpeed() > TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter = 0;
  }
}

unsigned long FlightCpu::getFlightTime()
{
  if (! inFlight) {
    return 0;
  }

  return (millis() - startFlightTime) / 1000;
}