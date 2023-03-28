#include <Adafruit_BMP085.h>

#define NUMBER_OF_PRESSURE_SAMPLES 6
#define SAMPLES 40
#define MAX_SAMPLES 50

class Variometer
{
    public:
        Variometer();
        void tick();
        unsigned int getPressure();
        unsigned int getAltitude();
        float getTemperature();
        float getVario();
        void setQnh(unsigned int qnh);
        void setQnhByAltitude(unsigned int altitude);

    private:
        Adafruit_BMP085 barometer;
        bool barometerInitialized = false;
        unsigned int qnh = 101325;
        unsigned int pressureSamples[NUMBER_OF_PRESSURE_SAMPLES];
        unsigned long lastTimeVarioWasCalculated = 0;
        unsigned int lastPressure = qnh;
        float vario = 0;
        float altitudeArray[MAX_SAMPLES + 1];
        float timeArray[MAX_SAMPLES + 1];

        void calcVario();
        unsigned int calcAltitude(unsigned int pressure);
        unsigned int getAveragePressure(unsigned int newPressure);
};
