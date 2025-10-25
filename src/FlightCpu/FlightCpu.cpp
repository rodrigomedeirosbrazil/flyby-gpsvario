#include "FlightCpu.h"
#include "../globals.h"
#include "../Barometer/Barometer.h"
#include "../Variometer/Variometer.h"
#include "../Beep/Beep.h"
#include "../Gps/Gps.h"
#include "../Wind/Wind.h"
#include "../Screen/Screen.h"
#include "../Thermal/Thermal.h"
#include "../Config/Config.h"

FlightCpu::FlightCpu() {
}

void FlightCpu::tick() {
    if (barometer.isAvailable()) {
      variometer.tick(barometer.getPressure(), millis());
    }

    // Usar configuração para controlar se o beep só funciona em voo
    Config& config = Config::getInstance();
    if (inFlight || !config.getVarioBeepOnlyInFlight()) {
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
  Config& config = Config::getInstance();
  if (!config.getQnhByGps() || !gps.isReliable() || smallerVdop <= gps.getVdop()) {
    return;
  }

  smallerVdop = gps.getVdop();
  variometer.setQnhByAltitude(gps.getAltitude());
}

void FlightCpu::checkInFlight() {
  Config& config = Config::getInstance();
  uint8_t takeoffSpeed = config.getTakeoffSpeed();
  
  if (! inFlight && gps.isReliable() && gps.getSpeed() > takeoffSpeed && inFlightCounter == 4) {
    inFlight = true;
    inFlightCounter = 0;
    startFlightTime = millis();
    oneUpSound();
  } else if (! inFlight && gps.isReliable() && gps.getSpeed() > takeoffSpeed && inFlightCounter < 4) {
    inFlightCounter++;
  } else if (! inFlight && gps.isReliable() && gps.getSpeed() < takeoffSpeed && inFlightCounter < 4) {
    inFlightCounter = 0;
  } else if (inFlight && gps.isReliable() && gps.getSpeed() < takeoffSpeed && inFlightCounter == 4) {
    inFlight = false;
    inFlightCounter = 0;
    fireballSound();
    fireballSound();
    fireballSound();
  } else if (inFlight && gps.isReliable() && gps.getSpeed() < takeoffSpeed && inFlightCounter < 4) {
    inFlightCounter++;
  } else if (inFlight && gps.isReliable() && gps.getSpeed() > takeoffSpeed && inFlightCounter < 4) {
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