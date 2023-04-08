#include "FlightCpu.h"

FlightCpu::FlightCpu(
    Variometer *variometer,
    Gps *gps,
    Beep *beep,
    Screen *screen
) {
    this->variometer = variometer;
    this->gps = gps;
    this->beep = beep;
    this->screen = screen;
}

void FlightCpu::tick() {
    bySecondTask();
}

void FlightCpu::bySecondTask() {
    if (millis() - lastTimeBySecondTask < 1000) {
        return;
    }
    lastTimeBySecondTask = millis();

    autoAdjustQNH();
    checkInFlight();
}

void FlightCpu::autoAdjustQNH() {
  if (! gps->isAvailable() || smallerVdop <= gps->getVdop()) {
    return;
  }

  smallerVdop = gps->getVdop();
  variometer->setQnhByAltitude(gps->getAltitude());
  coinSound();
}

void FlightCpu::checkInFlight() {
  if (! inFlight && gps->getSpeed() > TAKEOFF_SPEED && inFlightCounter == 4) {
    inFlight = true;
    startFlightTime = millis(); // TODO: change to timestamp
    oneUpSound();
  } else if (! inFlight && gps->getSpeed() > TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter++;
  } else if (! inFlight && gps->getSpeed() < TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter = 0;
  } else if (inFlight && gps->getSpeed() < TAKEOFF_SPEED && inFlightCounter == 4) {
    inFlight = false;
    fireballSound();
    fireballSound();
    fireballSound();
  } else if (inFlight && gps->getSpeed() < TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter++;
  } else if (inFlight && gps->getSpeed() > TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter = 0;
  }
}

unsigned long FlightCpu::getFlightTime()
{
  if (! inFlight) {
    return 0;
  }

  return millis() - startFlightTime;
}