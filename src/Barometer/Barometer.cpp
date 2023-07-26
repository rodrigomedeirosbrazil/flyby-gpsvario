#include <string.h>
#include "Barometer.h"

Barometer::Barometer() {
  #ifndef NO_BAROMETER
  if (barometer.begin(BMP085_ULTRAHIGHRES)) {
    this->barometerInitialized = true;
  }
  #endif
}

bool Barometer::isAvailable()
{
  return this->barometerInitialized;
}

long Barometer::getPressure()
{
  return barometer.readPressure();
}

float Barometer::getTemperature()
{
  if (! this->barometerInitialized) {
    return 0;
  }

  return barometer.readTemperature();
}