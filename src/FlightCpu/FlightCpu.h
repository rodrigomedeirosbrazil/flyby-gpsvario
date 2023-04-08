#ifndef FLIGHTCPU_H
#define FLIGHTCPU_H

#include "../Variometer/Variometer.h"
#include "../Gps/Gps.h"
#include "../Beep/Beep.h"
#include "../Screen/Screen.h"
#include "../defines.h"
#include "../helpers/helpers.h"

class FlightCpu
{
    public:
        FlightCpu(
            Variometer *variometer,
            Gps *gps,
            Beep *beep,
            Screen *screen
        );
        void tick();
        void autoAdjustQNH();
        unsigned long getFlightTime();

    private:
        void bySecondTask();
        void checkInFlight();

        Variometer *variometer;
        Gps *gps;
        Beep *beep;
        Screen *screen;

        unsigned long smallerVdop = 9999;
        unsigned long lastTimeBySecondTask = 0;
        bool inFlight = false;
        unsigned long startFlightTime;
        byte inFlightCounter = 0;
};

#endif