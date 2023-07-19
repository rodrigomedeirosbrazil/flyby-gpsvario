#include <string.h>
#include "Wind.h"

// #include <iostream>
// using namespace std;

Wind::Wind()
{
  timeout = 300000;
  speed = 0;
  direction = 0;
  lastCalculedWind = 0;
  memset(speeds, 0, sizeof(speeds));
  memset(times, 0, sizeof(times));
}

bool Wind::isAvailable()
{
  if (speed == 0 && direction == 0) {
    return false;
  }

  return true;
}

void Wind::storeSpeed(unsigned long heading, float speed, unsigned long now)
{
  int cardinalDirection = (int)((heading + 11.25f) / 22.5f) % 16;
  if (now - times[cardinalDirection] < timeout && speeds[cardinalDirection] != 0) {
      speeds[cardinalDirection] = (speeds[cardinalDirection] + speed) / 2;
      times[cardinalDirection] = now;
  } else {
      speeds[cardinalDirection] = speed;
      times[cardinalDirection] = now;
  }
  calcWind(now);
}

float Wind::getSpeed()
{
  return speed;
}

unsigned long Wind::getDirection()
{
  return direction;
}

void Wind::calcWind(unsigned long now)
{
  int maxIndex = 0;
  for (int i = 0; i < 16; i++) {
    if (speeds[i] > speeds[maxIndex]) {
      maxIndex = i;
    }
  }
  // cout << "maxIndex " << maxIndex << endl;
  // cout << "maxIndex speed " << speeds[maxIndex] << endl;

  if (now - times[maxIndex] > timeout) {
    return;
  }

  int minIndex = 0;
  for (int i = 0; i < 16; i++) {
    if (speeds[i] == 0) {
      continue;
    }

    if (
      speeds[i] < speeds[minIndex]
      || speeds[minIndex] == 0
    ) {
      minIndex = i;
    }
  }

  // cout << "minIndex " << minIndex << endl;
  // cout << "minIndex speed " << speeds[minIndex] << endl;

  if (now - times[minIndex] > timeout) {
    return;
  }

  int minIndexInverted = (minIndex + 8) % 16;
  // cout << "minIndexInverted " << minIndexInverted << endl;

  if (
      minIndexInverted == maxIndex
      || (minIndexInverted + 1) % 16 == maxIndex
      || (minIndexInverted - 1) % 16 == maxIndex
  ) {
    speed = speeds[maxIndex] - speeds[minIndex];
    direction = ((int)(minIndex * 22.5f)) % 360;
    lastCalculedWind = now;
  }
}
