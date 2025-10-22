#ifndef COMPASS_H
#define COMPASS_H

#include <U8g2lib.h>
#include "../defines.h"
#include "../Display/Display.h"

#define pi 3.141593

class Compass
{
    public:
        Compass();
        void draw();
    private:
        uint8_t x;
        uint8_t y;
        uint8_t size;
        unsigned int compassDegree;
        unsigned int heading;
        unsigned long windDirection;
        bool isWindAvailable = false;

        void drawCompassCircles();
        void drawNeedle();
        void drawCardinalPoint(int angleOffset, const char* letter);
        void drawCompassDegree(unsigned int degree);
        void drawWindDirection();
        void drawWaitingGps();
        void drawSatelliteCount();
};

#endif
