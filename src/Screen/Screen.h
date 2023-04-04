#ifndef SCREEN_H
#define SCREEN_H

#include "../defines.h"
#include "../Variometer/Variometer.h"
#include "../Compass/Compass.h"
#include "../Display/Display.h"
#include "../Gps/Gps.h"

#define GPS_SCREEN 0
#define INFO_SCREEN 1

class Screen
{
    public:
        Screen(Variometer *variometer, Gps *gps);
        void begin();
        void draw();

    private:
        unsigned char screenSelected = INFO_SCREEN;
        Compass *compass;
        Display *display;
        Variometer *variometer;
        Gps *gps;
        unsigned long lastTimeScreenWasDrawn = 0;
        const char notAvailableText[4] = "N/A";

        void drawGpsScreen();
        void drawInfoScreen();

        void drawInfoBox(char *value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
        void drawInfoBox (int value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
        void drawInfoBox (long value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
        void drawInfoBox (float value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
};

#endif
