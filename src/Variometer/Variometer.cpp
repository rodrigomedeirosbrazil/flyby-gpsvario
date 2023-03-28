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

  this->lastPressure = getAveragePressure(barometer.readPressure());
  calcVario();
}

void Variometer::calcVario()
{
  float N1 = 0;
  float N2 = 0;
  float N3 = 0;
  float D1 = 0;
  float D2 = 0;

  for(int cc = 1; cc <= MAX_SAMPLES; cc++)
  {
    this->altitudeArray[(cc - 1)] = this->altitudeArray[cc];
    this->timeArray[(cc - 1)] = this->timeArray[cc];
  };

  this->altitudeArray[MAX_SAMPLES] = this->getAltitude();
  this->timeArray[MAX_SAMPLES] = millis();

  float stime = this->timeArray[MAX_SAMPLES - SAMPLES];

  for(int cc = (MAX_SAMPLES - SAMPLES); cc < MAX_SAMPLES; cc++)
  {
    N1 += (this->timeArray[cc] - stime) * this->altitudeArray[cc];
    N2 += (this->timeArray[cc] - stime);
    N3 += (this->altitudeArray[cc]);
    D1 += (this->timeArray[cc] - stime) * (this->timeArray[cc] - stime);
    D2 += (this->timeArray[cc] - stime);
  };

  this->vario = 1000 
    * ((SAMPLES * N1) - N2 * N3) 
    / (SAMPLES * D1 - D2 * D2);
}

unsigned int Variometer::getPressure()
{
  this->lastPressure;
}

unsigned int Variometer::calcAltitude(unsigned int pressure)
{
  return 44330 * (1.0 - pow(pressure / this->qnh, 0.1903));
}

float Variometer::getTemperature()
{
  return barometer.readTemperature();
}

float Variometer::getVario()
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

unsigned int Variometer::getAveragePressure(unsigned int newPressure)
{
  memmove(
    &this->pressureSamples[1], 
    &this->pressureSamples, 
    sizeof(this->pressureSamples[0]) * (NUMBER_OF_PRESSURE_SAMPLES - 1)
  );

  this->pressureSamples[0] = newPressure;

  unsigned int sum = 0;
  for (unsigned i = 0; i < NUMBER_OF_PRESSURE_SAMPLES; i++) {
    sum += this->pressureSamples[i];
  }

  return sum / NUMBER_OF_PRESSURE_SAMPLES;
}


