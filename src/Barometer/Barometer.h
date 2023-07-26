#ifndef BAROMETER_H
#define BAROMETER_H

#include <Adafruit_BMP085.h>

class Barometer
{
    public:
        Barometer();
        long getPressure();
        float getTemperature();
        bool isAvailable();

    private:
        Adafruit_BMP085 barometer;
        bool barometerInitialized = false;
};

#endif
