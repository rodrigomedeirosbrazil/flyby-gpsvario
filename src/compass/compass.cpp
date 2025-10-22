#include <U8g2lib.h>
#include "compass.h"
#include "../globals.h"
#include "../Gps/Gps.h"
#include "../Wind/Wind.h"

Compass::Compass() {
  this->x = 27;
  this->y = 27;
  this->size = 27;
}

void Compass::draw()
{
  display.setFont(SMALL_FONT);

  if (gps.isAvailable()) {
    this->heading = gps.getHeading();
    this->compassDegree = 360 - this->heading;
    this->windDirection = wind.getDirection();
    this->isWindAvailable = wind.isAvailable();

    drawCompassCircles();
    drawNeedle();
    drawCardinalPoint(270, "N");
    drawCardinalPoint(90, "S");
    drawCardinalPoint(0, "E");
    drawCardinalPoint(180, "W");
    drawCompassDegree(this->heading);
    drawWindDirection();
  }

  if (!gps.isAvailable()) {
    drawWaitingGps();
  }
}

void Compass::drawCompassCircles()
{
  display.drawCircle(this->x, this->y, this->size);
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

void Compass::drawCardinalPoint(int angleOffset, const char* letter)
{
  unsigned char x = ((cos((this->compassDegree + angleOffset) * (pi / 180))) * (this->size - 5)) + this->x;
  unsigned char y = ((sin((this->compassDegree + angleOffset) * (pi / 180))) * (this->size - 5)) + this->y + 6;

  display.setCursor(x - (SMALL_FONT_WIDTH / 2), y - (SMALL_FONT_HEIGHT / 2));
  display.print(letter);
}

void Compass::drawCompassDegree(unsigned int degree)
{
  display.printCenter(
      (int) degree,
      this->x,
      this->y + this->size + SMALL_FONT_HEIGHT + 1);
}

void Compass::drawWindDirection()
{
  if (! this->isWindAvailable) {
    return;
  }

  // Starting position of the arrow (on the compass circle)
  unsigned char x = ((cos((this->compassDegree + this->windDirection - 90) * (pi / 180))) * (this->size - 10)) + this->x;
  unsigned char y = ((sin((this->compassDegree + this->windDirection - 90) * (pi / 180))) * (this->size - 10)) + this->y;

  // Calculate the angle of the arrow pointing to the center
  float angleToCenter = atan2(this->y - y, this->x - x);

  // Length of the main arrow and arrowhead
  int arrowLength = 10;
  int arrowHeadLength = 5;
  float arrowHeadAngle = 30 * (pi / 180); // 30 degrees

  // End point of the main line (pointing to the center)
  int endX = x + (cos(angleToCenter) * arrowLength);
  int endY = y + (sin(angleToCenter) * arrowLength);

  // Draw main arrow line
  display.drawLine(x, y, endX, endY);

  // Draw arrowhead (two lines forming the "V")
  // First line of the arrowhead
  int head1X = endX + (cos(angleToCenter + pi - arrowHeadAngle) * arrowHeadLength);
  int head1Y = endY + (sin(angleToCenter + pi - arrowHeadAngle) * arrowHeadLength);
  display.drawLine(endX, endY, head1X, head1Y);

  // Second line of the arrowhead
  int head2X = endX + (cos(angleToCenter + pi + arrowHeadAngle) * arrowHeadLength);
  int head2Y = endY + (sin(angleToCenter + pi + arrowHeadAngle) * arrowHeadLength);
  display.drawLine(endX, endY, head2X, head2Y);
}

void Compass::drawWaitingGps()
{
  this->compassDegree = 0;

  drawCompassCircles();
  drawNeedle();
  drawSatelliteCount();
}

void Compass::drawSatelliteCount()
{
  unsigned short satellites = gps.getSatellites();

  char buffer[8];

  if (satellites == 255 || satellites == 0) {
    sprintf(buffer, "--");
  }

  if (satellites < 255 && satellites > 0) {
    sprintf(buffer, "%d", satellites);
  }

  display.printCenter(
    buffer,
    this->x,
    this->y + this->size + SMALL_FONT_HEIGHT + 1
  );
}