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
        void getDateTime(
            int *year, 
            byte *month, 
            byte *day, 
            byte *hour, 
            byte *minute, 
            byte *second
        );

    private:
        TinyGPS *gpsParser;
        HardwareSerial *serial2;
        unsigned long lastTimeGpsWasTicked = 0;
        unsigned long gpsFixAge = 0;
        bool dataAvailable = false;
        float latitude = 0;
        float longitude = 0;
        float speed = 0;
        float altitude = 0;
        float heading = 0;
        unsigned long hdop = 0;
        unsigned long vdop = 0;
        unsigned short satellites = 0;

        void getParserData();
        bool gpsHasFreshData();
        bool isValidData();
};

#endif
