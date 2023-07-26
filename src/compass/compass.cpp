#include <U8g2lib.h>
#include "Compass.h"

Compass::Compass(Display *display, uint8_t x, uint8_t y, uint8_t size) {
  this->display = display;
  this->x = x;
  this->y = y;
  this->size = size;
}

void Compass::setHeading(unsigned int heading)
{
  this->heading = heading;
  this->compassDegree = 360 - heading;
}

void Compass::setWindDirection(unsigned long windDirection)
{
  this->windDirection = windDirection;
}

void Compass::setWindAvailabilty(bool isAvailable)
{
  this->isWindAvailable = isAvailable;
}

void Compass::draw()
{
  this->display->setFont(SMALL_FONT);
  drawCompassCircles();
  drawNeedle();
  drawNorth();
  drawSouth();
  drawEast();
  drawWest();
  drawCompassDegree(this->heading);
  drawWindSock();
}

void Compass::drawCompassCircles()
{
  this->display->drawCircle(this->x, this->y, this->size);
  this->display->drawCircle(this->x, this->y, this->size - 10);
}

void Compass::drawNeedle()
{
    this->display->drawLine(
        this->x, 
        this->y - 10,
        this->x - 5, 
        this->y + 10
    );

    this->display->drawLine(
        this->x, 
        this->y - 10,
        this->x + 5, 
        this->y + 10
    );

    this->display->drawLine(
        this->x, 
        this->y + 5,
        this->x - 5, 
        this->y + 10
    );

    this->display->drawLine(
        this->x, 
        this->y + 5,
        this->x + 5, 
        this->y + 10
    );
}

void Compass::drawNorth()
{
  unsigned char x = ((cos((this->compassDegree + 270) * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin((this->compassDegree + 270) * (pi / 180))) * (this->size - 5)) + this->y + 6;

  this->display->setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  this->display->print("N");
}

void Compass::drawSouth()
{
  unsigned char x = ((cos((this->compassDegree + 90) * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin((this->compassDegree + 90) * (pi / 180))) * (this->size - 5)) + this->y + 6;

  this->display->setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  this->display->print("S");
}

void Compass::drawEast()
{
  unsigned char x = ((cos(this->compassDegree * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin(this->compassDegree * (pi / 180))) * (this->size - 5)) + this->y + 6;

  this->display->setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  this->display->print("E");
}

void Compass::drawWest()
{
  unsigned char x = ((cos((this->compassDegree + 180) * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin((this->compassDegree + 180) * (pi / 180))) * (this->size - 5)) + this->y + 6;

  this->display->setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  this->display->print("W");
}

void Compass::drawCompassDegree(unsigned int degree)
{
  this->display->printCenter(
      (int) degree,
      this->x,
      this->y + this->size + SMALL_FONT_HEIGHT + 1);
}

void Compass::drawWindSock()
{
  if (! this->isWindAvailable) {
    return;
  }

  unsigned char x = ((cos((this->compassDegree + this->windDirection - 90) * (pi / 180))) * (this->size - 10)) + this->x;
  unsigned char y = ((sin((this->compassDegree + this->windDirection - 90) * (pi / 180))) * (this->size - 10)) + this->y + 6;

  this->display->setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  this->display->print("P");
}