#ifndef SCREEN_H
#define SCREEN_H

#include "../defines.h"
#include "../compass/compass.h"
#include "../Display/Display.h"
#include "../FlightCpu/FlightCpu.h"

#define INFOBOX_WIDTH 55
#define INFOBOX_HEIGHT 22

class Screen
{
    public:
        enum Screens {
            GpsScreen,
            InfoScreen
        };

        Screen();
        void begin();
        void draw();

    private:
        Screens screenSelected = InfoScreen;
        unsigned long lastTimeScreenWasDrawn = 0;
        const char notAvailableText[3] = "--";
        const char spinner[4] = {'-', '\\', '|', '/'};
        byte spinnerIndex = 0;
        static const unsigned long INFO_SCREEN_TIMEOUT = 10000;
        unsigned long systemStartTime = 0;

        void drawGpsScreen();
        void drawInfoScreen();
        bool isInfoScreenTimeoutExpired();

        void drawInfoBox(const char* label, char *value, const char* unit, uint8_t offset, bool isAvailable);
        void drawInfoBox(const char* label, int value, const char* unit, uint8_t offset, bool isAvailable);
        void drawInfoBox(const char* label, long value, const char* unit, uint8_t offset, bool isAvailable);
        void drawInfoBox(const char* label, float value, const char* unit, uint8_t offset, bool isAvailable);
        void drawWindSpeedBox();
        void drawGpsAltitudeBox();
};

#endif
