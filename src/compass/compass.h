
#include <U8g2lib.h>

#define pi 3.141593

extern U8G2_SSD1306_128X64_NONAME_1_HW_I2C display;

class Compass
{
    public:
        Compass(uint8_t x, uint8_t y, uint8_t size);
        void draw(uint8_t degree);
    private:
        uint8_t x;
        uint8_t y;
        uint8_t size;
        uint8_t compassDegree;

        void drawCompassCircles();
        void drawNeedle();
        void drawNorth();
        void drawSouth();
        void drawEast();
        void drawWest();
        void drawCompassDegree(uint8_t degree);
};
