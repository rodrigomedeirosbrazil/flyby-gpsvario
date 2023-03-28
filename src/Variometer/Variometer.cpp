#include <string.h>
#include "Variometer.h"

Variometer::Variometer() {
   if (barometer.begin(BMP085_ULTRAHIGHRES)) {
    this->barometerInitialized = true;
  }
}

void Variometer::tick()
{
  if (! this->barometerInitialized) {
    return;
  }

  shiftPressureSamples();
  pressureSamples[0] = barometer.readPressure();

  if (millis() - this->lastTimeVarioWasCalculated > 1000) {
    this->lastTimeVarioWasCalculated = millis();
    unsigned int pressure = calcAveragePressure();
    this->vario = calcAltitude(pressure) - calcAltitude(this->lastPressure);
    this->lastPressure = pressure;
  }
}

unsigned int Variometer::calcAveragePressure()
{
  unsigned int sum = 0;

  for (unsigned i = 0; i < NUMBER_OF_SAMPLES; i++)
  {
    sum += this->pressureSamples[i];
  }

  return sum / NUMBER_OF_SAMPLES;
}

unsigned int Variometer::getPressure()
{
  this->lastPressure;
}

unsigned int Variometer::calcAltitude(unsigned int pressure)
{
  return 44330 * (1.0 - pow(pressure / this->qnh, 0.1903));
}

char Variometer::getTemperature()
{
  return barometer.readTemperature();
}

char Variometer::getVario()
{
  return this->vario;
}

unsigned int Variometer::getAltitude()
{
  return calcAltitude(this->lastPressure);
}

void Variometer::setQnh(unsigned int qnh)
{
  this->qnh = qnh;
}

void Variometer::setQnhByAltitude(unsigned int altitude)
{
  setQnh(this->lastPressure / pow(1.0 - altitude / 44330.0, 5.255));
}

void Variometer::shiftPressureSamples()
{
  memmove(
    &this->pressureSamples[1], 
    &this->pressureSamples, 
    sizeof(this->pressureSamples[0]) * (NUMBER_OF_SAMPLES - 1)
  );
}


