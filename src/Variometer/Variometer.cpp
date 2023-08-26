#include <string.h>
#include <cmath>
#include "Variometer.h"
#include "../KalmanFilter4d/kalmanfilter4d.h"

Variometer::Variometer() {
    kalmanFilter4d_configure(0, 0, 1.0f, 0.0f, 0.0f);
}

void Variometer::tick(long pressure, long nowMsec)
{
  this->lastPressure = getAveragePressure(pressure);
  calcVario(nowMsec);
}

void Variometer::calcVario(long nowMsec)
{
  float KFAltitudeCm, KFClimbrateCps;

  float elapsedTimeMsec = nowMsec - lastTimeVarioWasCalculatedMsec;
  lastTimeVarioWasCalculatedMsec = nowMsec;

  kalmanFilter4d_predict(elapsedTimeMsec / 1000.0f);

  float altitudeMeters = calcAltitude(this->lastPressure);
  kalmanFilter4d_update(altitudeMeters * 100, 0, (float*)&KFAltitudeCm, (float*)&KFClimbrateCps);

  this->vario = KFClimbrateCps / 100.0f;
}

long Variometer::getPressure()
{
  return this->lastPressure;
}

float Variometer::calcAltitude(long pressure)
{
  return 44330 * (1.0 - pow((float) pressure / (float) this->qnh, 0.1903));
}

float Variometer::getVario()
{
  return this->vario;
}

float Variometer::getAltitude()
{
  return calcAltitude(this->lastPressure);
}

void Variometer::setQnh(long qnh)
{
  this->qnh = qnh;
}

long Variometer::getQnh()
{
  return this->qnh;
}

void Variometer::setQnhByAltitude(float altitude)
{
  setQnh(this->lastPressure / pow(1.0 - altitude / 44330.0, 5.255));
}

long Variometer::getAveragePressure(long newPressure)
{

  if (lastTimeVarioWasCalculatedMsec == 0) {
    for (unsigned i = 0; i < NUMBER_OF_PRESSURE_SAMPLES; i++) {
      this->pressureSamples[i] = newPressure;
    }
    return newPressure;
  }

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



