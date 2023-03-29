
#include <U8g2lib.h>
#include "../defines.h"

#define pi 3.141593

#ifdef WOKWI
extern U8G2_SSD1306_128X64_NONAME_1_HW_I2C display;
#endif

#ifdef SMARTVARIO
extern U8G2_ST7565_JLX12864_1_4W_SW_SPI display;
#endif

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
