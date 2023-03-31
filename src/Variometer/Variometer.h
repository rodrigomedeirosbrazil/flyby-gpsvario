#ifndef VARIOMETER_H
#define VARIOMETER_H

#include <Adafruit_BMP085.h>

#define NUMBER_OF_PRESSURE_SAMPLES 6
#define SAMPLES 40
#define MAX_SAMPLES 50

class Variometer
{
    public:
        Variometer();
        void tick();
        long getPressure();
        int getAltitude();
        float getTemperature();
        float getVario();
        void setQnh(long qnh);
        long getQnh();
        void setQnhByAltitude(int altitude);

    private:
        Adafruit_BMP085 barometer;
        bool barometerInitialized = false;
        long qnh = 101325;
        long pressureSamples[NUMBER_OF_PRESSURE_SAMPLES];
        unsigned long lastTimeVarioWasCalculated = 0;
        long lastPressure = qnh;
        float vario = 0;
        float altitudeArray[MAX_SAMPLES + 1];
        float timeArray[MAX_SAMPLES + 1];

        void calcVario();
        int calcAltitude(long pressure);
        long getAveragePressure(long newPressure);
};

#endif
