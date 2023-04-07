#ifndef SCREEN_H
#define SCREEN_H

#include "../defines.h"
#include "../Variometer/Variometer.h"
#include "../Compass/Compass.h"
#include "../Display/Display.h"
#include "../Gps/Gps.h"


class Screen
{
    public:
        enum Screens {
            GpsScreen,
            InfoScreen
        };

        Screen(Variometer *variometer, Gps *gps);
        void begin();
        void draw();

    private:
        Screens screenSelected = InfoScreen;
        Compass *compass;
        Display *display;
        Variometer *variometer;
        Gps *gps;
        unsigned long lastTimeScreenWasDrawn = 0;
        const char notAvailableText[4] = "N/A";
        const char spinner[4] = {'-', '\\', '|', '/'};
        byte spinnerIndex = 0;

        void drawGpsScreen();
        void drawInfoScreen();

        void drawInfoBox(char *value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
        void drawInfoBox (int value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
        void drawInfoBox (long value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
        void drawInfoBox (float value, char* unit, uint8_t x, uint8_t y, bool isAvailable);
};

#endif
