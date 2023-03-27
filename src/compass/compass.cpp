#include <U8g2lib.h>
#include "compass.h"
#include "../helper/helper.h"

#define pi 3.141593

// unsigned int degree;
// unsigned char compassX;
// unsigned char compassY;
// unsigned char compassSize;

void drawCompass() {
    display.setFont(u8g_font_5x7);
    drawCompassCircles();
    drawNorth();
    drawSouth();
    drawEast();
    drawWest();
    drawCompassDegree();
}

void drawCompassCircles()
{
    display.drawCircle(compassX, compassY, compassSize);
    display.drawCircle(compassX, compassY, compassSize - 10);
}

void drawNorth()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos((compassDegree + 270) * (pi / 180))) * (compassSize - 5)) + compassX;
    unsigned char y = ((sin((compassDegree + 270) * (pi / 180))) * (compassSize - 5)) + compassY + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("N");
}

void drawSouth()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos((compassDegree + 90) * (pi / 180))) * (compassSize - 5)) + compassX;
    unsigned char y = ((sin((compassDegree + 90) * (pi / 180))) * (compassSize - 5)) + compassY + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("S");
}

void drawEast()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos(compassDegree * (pi / 180))) * (compassSize - 5)) + compassX;
    unsigned char y = ((sin(compassDegree * (pi / 180))) * (compassSize - 5)) + compassY + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("E");
}

void drawWest()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos((compassDegree + 180) * (pi / 180))) * (compassSize - 5)) + compassX;
    unsigned char y = ((sin((compassDegree + 180) * (pi / 180))) * (compassSize - 5)) + compassY + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("W");
}

void drawCompassDegree()
{
    printNumberCenter(
        degree,
        compassX,
        compassY + compassSize + display.getMaxCharHeight() + 1);
}
