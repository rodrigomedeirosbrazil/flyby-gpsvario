#ifndef FLIGHTCPU_H
#define FLIGHTCPU_H

#include "../defines.h"
#include "../helpers/helpers.h"
#include "../Variometer/Variometer.h"
#include "../Gps/Gps.h"
#include "../Beep/Beep.h"
#include "../Screen/Screen.h"
#include "../Wind/Wind.h"
#include "../Barometer/Barometer.h"

class FlightCpu
{
    public:
        FlightCpu();
        void tick();
        void autoAdjustQNH();
        unsigned long getFlightTime();
        inline unsigned long getSmallerVdop() { return smallerVdop; }

    private:
        void bySecondTask();
        void checkInFlight();

        unsigned long smallerVdop = 9999;
        unsigned long lastTimeBySecondTask = 0;
        bool inFlight = false;
        unsigned long startFlightTime;
        byte inFlightCounter = 0;
};

#endif