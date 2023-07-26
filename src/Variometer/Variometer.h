#ifndef VARIOMETER_H
#define VARIOMETER_H

#define NUMBER_OF_PRESSURE_SAMPLES 6
#define SAMPLES 40
#define MAX_SAMPLES 50

class Variometer
{
    public:
        Variometer();
        void tick(long pressure, long now);
        long getPressure();
        float getAltitude();
        float getVario();
        void setQnh(long qnh);
        long getQnh();
        void setQnhByAltitude(float altitude);

    private:
        long qnh = 101325;
        long pressureSamples[NUMBER_OF_PRESSURE_SAMPLES];
        unsigned long lastTimeVarioWasCalculated = 0;
        long lastPressure = qnh;
        float vario = 0;
        long pressureArray[MAX_SAMPLES + 1];
        float timeArray[MAX_SAMPLES + 1];

        void calcVario(long now);
        float calcAltitude(long pressure);
        long getAveragePressure(long newPressure);
};

#endif
