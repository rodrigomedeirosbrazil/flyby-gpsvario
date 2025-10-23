#include <U8g2lib.h>
#include "compass.h"
#include "../globals.h"
#include "../Gps/Gps.h"
#include "../Wind/Wind.h"

// GPS icon bitmap (15x15 pixels)
static const unsigned char image_GPS_ICON_bits[] = {0xe0,0x0f,0x00,0x18,0xc4,0x33,0x0a,0x64,0x12,0x48,0xa1,0x53,0xc1,0x53,0x81,0x53,0x01,0x51,0x01,0x42,0x02,0x04,0x02,0x08,0x04,0x10,0x18,0x0c,0xe0,0x03};

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
    return;
  }

  drawWaitingGps();
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
  unsigned char y = ((sin((this->compassDegree + angleOffset) * (pi / 180))) * (this->size - 5)) + this->y + 8;

  display.setFont(MEDIUM_FONT);
  display.setCursor(x - (MEDIUM_FONT_WIDTH / 2), y - (MEDIUM_FONT_HEIGHT / 2));
  display.print(letter);
}

void Compass::drawCompassDegree(unsigned int degree)
{
  display.setFont(SMALL_FONT);
  display.printCenter(
      (int) degree,
      27,
      63
  );
}

void Compass::drawWindDirection()
{
  if (! this->isWindAvailable) {
    return;
  }

  // Starting position of the arrow (on the compass circle)
  unsigned char x = ((cos((this->compassDegree + this->windDirection - 90) * (pi / 180))) * (this->size - 8)) + this->x;
  unsigned char y = ((sin((this->compassDegree + this->windDirection - 90) * (pi / 180))) * (this->size - 8)) + this->y;

  // Calculate the angle of the arrow pointing to the center
  float angleToCenter = atan2(this->y - y, this->x - x);

  // Length of the main arrow and arrowhead
  int arrowLength = 8;
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
  drawGpsIcon();
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

  display.setFont(SMALL_FONT);
  display.printCenter(
    buffer,
    27,
    63
  );
}

void Compass::drawGpsIcon()
{
  display.drawXBM(20, 20, 15, 15, image_GPS_ICON_bits);
}