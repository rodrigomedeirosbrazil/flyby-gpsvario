#ifndef VARIOMETER_H
#define VARIOMETER_H

#define NUMBER_OF_PRESSURE_SAMPLES 20

class Variometer
{
    public:
        Variometer();
        void tick(long pressure, long nowMsec);
        long getPressure();
        float getAltitude();
        float getVario();
        void setQnh(long qnh);
        long getQnh();
        void setQnhByAltitude(float altitude);

    private:
        long qnh = 101325;
        long pressureSamples[NUMBER_OF_PRESSURE_SAMPLES];
        unsigned long lastTimeVarioWasCalculatedMsec = 0;
        long lastPressure = qnh;
        float vario = 0;

        void calcVario(long nowMsec);
        float calcAltitude(long pressure, bool useQnh = true);
        long getAveragePressure(long newPressure);
};

#endif
