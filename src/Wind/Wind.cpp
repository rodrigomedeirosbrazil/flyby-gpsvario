#include "Wind.h"

bool Wind::isAvailable()
{
  if (speed == 0 && direction == 0) {
    return false;
  }

  return true;
}

void Wind::storeSpeed(unsigned long heading, float speed)
{
  int cardinalDirection = (int)((heading + 11.25f) / 22.5f) % 16;
  if (millis() - times[cardinalDirection] < timeout && speeds[cardinalDirection] != 0) {
      speeds[cardinalDirection] = (speeds[cardinalDirection] + speed) / 2;
      times[cardinalDirection] = millis();
  } else {
      speeds[cardinalDirection] = speed;
      times[cardinalDirection] = millis();
  }
  calcWind();
}

float Wind::getSpeed()
{
  return speed;
}

unsigned long Wind::getDirection()
{
  return direction;
}

void Wind::calcWind()
{
  int maxIndex = 0;
  for (int i = 0; i < 16; i++) {
    if (speeds[i] > speeds[maxIndex]) {
      maxIndex = i;
    }
  }

  if (millis() - times[maxIndex] > timeout) {
    return;
  }

  int minIndex = 0;
  for (int i = 0; i < 16; i++) {
    if (speeds[i] < speeds[minIndex]) {
      minIndex = i;
    }
  }

  if (millis() - times[minIndex] > timeout) {
    return;
  }

  int minIndexInverted = (minIndex + 8) % 16;

  if (
      minIndexInverted == maxIndex
      || (minIndexInverted + 1) % 16 == maxIndex
      || (minIndexInverted - 1) % 16 == maxIndex
  ) {
    speed = speeds[maxIndex] - speeds[minIndex];
    direction = ((int)(maxIndex * 22.5f + 11.25f)) % 360;
    lastCalculedWind = millis();
  }
}
