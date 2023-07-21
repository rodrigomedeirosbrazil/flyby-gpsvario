
#include <U8g2lib.h>
#include "../defines.h"
#include "../Display/Display.h"

#define pi 3.141593

class Compass
{
    public:
        Compass(Display *display, uint8_t x, uint8_t y, uint8_t size);
        void draw();
        void setHeading(unsigned int heading);
        void setWindDirection(unsigned long windDirection);
        void setWindAvailabilty(bool isAvailable);
    private:
        uint8_t x;
        uint8_t y;
        uint8_t size;
        unsigned int compassDegree;
        Display *display;
        unsigned int heading;
        unsigned long windDirection;
        bool isWindAvailable = false;

        void drawCompassCircles();
        void drawNeedle();
        void drawNorth();
        void drawSouth();
        void drawEast();
        void drawWest();
        void drawCompassDegree(unsigned int degree);
        void drawWindSock();
};
