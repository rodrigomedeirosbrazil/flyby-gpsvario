#include "FlightCpu.h"

FlightCpu::FlightCpu() {
    this->variometer = new Variometer();
    this->beep = new Beep(SPEAKER_PIN);
    this->gps = new Gps();
    this->screen = new Screen(this);
    this->wind = new Wind();

    this->screen->begin();
}

Variometer* FlightCpu::getVariometer() {
    return this->variometer;
}

Gps* FlightCpu::getGps() {
    return this->gps;
}

Beep* FlightCpu::getBeep() {
    return this->beep;
}

Screen* FlightCpu::getScreen() {
    return this->screen;
}

Wind* FlightCpu::getWind() {
    return this->wind;
}

void FlightCpu::tick() {
    variometer->tick();
    
    if (inFlight) {
      beep->tick(this->variometer->getVario());
    }

    gps->tick();
    screen->draw();

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
      wind->storeSpeed(gps->getHeading(), gps->getSpeed());
    }
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
    inFlightCounter = 0;
    startFlightTime = millis(); // TODO: change to timestamp
    oneUpSound();
  } else if (! inFlight && gps->getSpeed() > TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter++;
  } else if (! inFlight && gps->getSpeed() < TAKEOFF_SPEED && inFlightCounter < 4) {
    inFlightCounter = 0;
  } else if (inFlight && gps->getSpeed() < TAKEOFF_SPEED && inFlightCounter == 4) {
    inFlight = false;
    inFlightCounter = 0;
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

  return (millis() - startFlightTime) / 1000;
}