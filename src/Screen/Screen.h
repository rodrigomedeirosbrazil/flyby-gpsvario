#include <U8g2lib.h>
#include "../defines.h"
#include "../Compass/Compass.h"

#define GPS_SCREEN 0

#ifdef WOKWI
extern U8G2_SSD1306_128X64_NONAME_1_HW_I2C display;
#endif

#ifdef SMARTVARIO
extern U8G2_ST7565_JLX12864_1_4W_SW_SPI display;
#endif

class Screen
{
    public:
        Screen();
        void draw();
        void setDegree(unsigned int degree);
        void setAltitude(unsigned int altitude);
        void setSpeed(unsigned int speed);
        void setVario(char vario);

    private:
        unsigned char screenSelected = GPS_SCREEN;
        Compass compass;
        unsigned long lastTimeScreenWasDrawn = 0;
        unsigned int degree=0;
        unsigned int altitude=0;
        unsigned int speed=0;
        char vario=0;

        void drawGpsScreen();
};
