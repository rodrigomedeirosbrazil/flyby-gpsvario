
#include <U8g2lib.h>
#include "../defines.h"
#include "../Display/Display.h"

#define pi 3.141593

class Compass
{
    public:
        Compass(Display *display, uint8_t x, uint8_t y, uint8_t size);
        void draw(unsigned int degree);
    private:
        uint8_t x;
        uint8_t y;
        uint8_t size;
        unsigned int compassDegree;
        Display *display;

        void drawCompassCircles();
        void drawNeedle();
        void drawNorth();
        void drawSouth();
        void drawEast();
        void drawWest();
        void drawCompassDegree(unsigned int degree);
};
