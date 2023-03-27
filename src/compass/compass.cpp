#include <U8g2lib.h>
#include "compass.h"
#include "../helper/helper.h"

#define pi 3.141593
#define COMPASS_X 25
#define COMPASS_Y 25
#define COMPASS_SIZE 25

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
    display.drawCircle(COMPASS_X, COMPASS_Y, COMPASS_SIZE);
    display.drawCircle(COMPASS_X, COMPASS_Y, COMPASS_SIZE - 10);
}

void drawNorth()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos((compassDegree + 270) * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_X;
    unsigned char y = ((sin((compassDegree + 270) * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_Y + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("N");
}

void drawSouth()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos((compassDegree + 90) * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_X;
    unsigned char y = ((sin((compassDegree + 90) * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_Y + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("S");
}

void drawEast()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos(compassDegree * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_X;
    unsigned char y = ((sin(compassDegree * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_Y + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("E");
}

void drawWest()
{
    unsigned int compassDegree = 360 - degree;
    unsigned char x = ((cos((compassDegree + 180) * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_X;
    unsigned char y = ((sin((compassDegree + 180) * (pi / 180))) * (COMPASS_SIZE - 5)) + COMPASS_Y + 6;

    display.setCursor(x - (display.getMaxCharWidth() / 2), y - (display.getMaxCharHeight() / 2));
    display.print("W");
}

void drawCompassDegree()
{
    printNumberCenter(
        degree,
        COMPASS_X,
        COMPASS_Y + COMPASS_SIZE + display.getMaxCharHeight() + 1);
}
