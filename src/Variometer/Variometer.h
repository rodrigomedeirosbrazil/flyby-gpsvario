#include <Adafruit_BMP085.h>

#define NUMBER_OF_SAMPLES 25

class Variometer
{
    public:
        Variometer();
        void tick();
        unsigned int getPressure();
        unsigned int getAltitude();
        char getTemperature();
        char getVario();
        void setQnh(unsigned int qnh);
        void setQnhByAltitude(unsigned int altitude);

    private:
        Adafruit_BMP085 barometer;
        bool barometerInitialized = false;
        unsigned int qnh = 101325;
        unsigned int pressureSamples[NUMBER_OF_SAMPLES];
        unsigned long lastTimeVarioWasCalculated = 0;
        unsigned int lastPressure = qnh;
        char vario = 0;

        void shiftPressureSamples();
        unsigned int calcAltitude(unsigned int pressure);
        unsigned int calcAveragePressure();
};
