#include <U8g2lib.h>
#include "../defines.h"
#include "../Compass/Compass.h"
#include "../Display/Display.h"

#define GPS_SCREEN 0

class Screen
{
    public:
        Screen();
        void begin();
        void draw();
        void setDegree(unsigned int degree);
        void setAltitude(unsigned int altitude);
        void setSpeed(unsigned int speed);
        void setVario(float vario);

    private:
        unsigned char screenSelected = GPS_SCREEN;
        Compass *compass;
        Display *display;
        unsigned long lastTimeScreenWasDrawn = 0;
        unsigned int degree=0;
        unsigned int altitude=0;
        unsigned int speed=0;
        float vario=0;

        void drawGpsScreen();
        void drawInfoBox(char *value, char* unit, uint8_t x, uint8_t y);
        void drawInfoBox (int value, char* unit, uint8_t x, uint8_t y);
        void drawInfoBox (float value, char* unit, uint8_t x, uint8_t y);
};
