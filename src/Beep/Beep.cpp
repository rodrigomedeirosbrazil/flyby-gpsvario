#include <Arduino.h>
#include "Beep.h"

Beep::Beep(unsigned char pin)
{
    this->pin = pin;
    pinMode(this->pin, OUTPUT);
}

void Beep::tick(float vario)
{
  unsigned long time = millis();
  if ((time - this->beep) > this->beepTime) {
    this->beep = time;

    if (vario > this->climbRate && vario < 15 )
    {
      this->beepTime = min(1000, 350 - (vario * 5));
      tone(
        this->pin, 
        max(100, (1000 + (100 * vario))), 
        min(1000, 300 - (vario * 5))
      );
    }
    else if (vario < this->sinkRate)
    {
      this->beepTime=200;
      tone(this->pin, 300, 340);
    }
  }
}

void Beep::setClimbRate(float climbRate)
{
    this->climbRate = climbRate;
}

void Beep::setSinkRate(float sinkRate)
{
    this->sinkRate = sinkRate;
}