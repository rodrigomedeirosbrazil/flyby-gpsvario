#include <U8g2lib.h>
#include "compass.h"
#include "../helper/helper.h"

Compass::Compass(uint8_t x, uint8_t y, uint8_t size) {
  this->x = x;
  this->y = y;
  this->size = size;
}

void Compass::draw(uint8_t degree)
{
  this->compassDegree = 360 - degree;

  display.setFont(SMALL_FONT);
  drawCompassCircles();
  drawNeedle();
  drawNorth();
  drawSouth();
  drawEast();
  drawWest();
  drawCompassDegree(degree);
}

void Compass::drawCompassCircles()
{
  display.drawCircle(this->x, this->y, this->size);
  display.drawCircle(this->x, this->y, this->size - 10);
}

void Compass::drawNeedle()
{
    display.drawLine(
        this->x, 
        this->y - 10,
        this->x - 5, 
        this->y + 10
    );

    display.drawLine(
        this->x, 
        this->y - 10,
        this->x + 5, 
        this->y + 10
    );

    display.drawLine(
        this->x, 
        this->y + 5,
        this->x - 5, 
        this->y + 10
    );

    display.drawLine(
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

  display.setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  display.print("N");
}

void Compass::drawSouth()
{
  unsigned char x = ((cos((this->compassDegree + 90) * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin((this->compassDegree + 90) * (pi / 180))) * (this->size - 5)) + this->y + 6;

  display.setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  display.print("S");
}

void Compass::drawEast()
{
  unsigned char x = ((cos(this->compassDegree * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin(this->compassDegree * (pi / 180))) * (this->size - 5)) + this->y + 6;

  display.setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  display.print("E");
}

void Compass::drawWest()
{
  unsigned char x = ((cos((this->compassDegree + 180) * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin((this->compassDegree + 180) * (pi / 180))) * (this->size - 5)) + this->y + 6;

  display.setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  display.print("W");
}

void Compass::drawCompassDegree(uint8_t degree)
{
  printNumberCenter(
      degree,
      this->x,
      this->y + this->size + SMALL_FONT_HEIGHT + 1);
}
