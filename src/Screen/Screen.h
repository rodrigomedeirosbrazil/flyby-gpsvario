#ifndef SCREEN_H
#define SCREEN_H

#include "../defines.h"
#include "../Compass/Compass.h"
#include "../Display/Display.h"
#include "../FlightCpu/FlightCpu.h"

#define INFOBOX_WIDTH 64
#define INFOBOX_HEIGHT 20

class FlightCpu;
class Screen
{
    public:
        enum Screens {
            GpsScreen,
            InfoScreen
        };

        Screen(FlightCpu *flightCpu);
        void begin();
        void draw();

    private:
        Screens screenSelected = InfoScreen;
        Compass *compass;
        Display *display;
        FlightCpu *flightCpu;
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
