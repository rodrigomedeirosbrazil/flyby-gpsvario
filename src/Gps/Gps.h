#ifndef GPS_H
#define GPS_H

#include <HardwareSerial.h>
#include "../defines.h"
#include "../TinyGPS/TinyGPS.h"

class Gps
{
    public:
        Gps();
        void tick();
        bool isAvailable();
        byte getBestVdop();
        float getLatitude();
        float getLongitude();
        float getSpeed();
        float getAltitude();
        float getHeading();
        unsigned long getHdop();
        unsigned long getVdop();
        unsigned short getSatellites();
        unsigned long getDate();
        unsigned long getTime();

    private:
        TinyGPS *gpsParser;
        HardwareSerial *serial2;
        unsigned long lastTimeGpsWasTicked = 0;
        unsigned long gpsFixAge = 0;
        bool dataAvailable = false;
        float latitude = 0;
        float longitude = 0;

        void getParserData();
        bool gpsHasFreshData();
        bool isValidData();
};

#endif
