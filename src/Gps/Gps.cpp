#include "Gps.h"
#include "../defines.h"

/*
$GPGGA,232000,2358.439,S,04618.474,W,1,08,0.9,545.4,M,46.9,M,,*4A
$GPRMC,232000,A,2358.439,S,04618.474,W,022.4,090.0,050616,003.1,W*6D
$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39

TinyGPSCustom gps_fix(gps, "GPGSA", 2);
TinyGPSCustom gps_pdop(gps, "GPGSA", 15);
TinyGPSCustom gps_vdop(gps, "GPGSA", 17);

eg3. $GPGGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh
1    = UTC of Position
2    = Latitude
3    = N or S
4    = Longitude
5    = E or W
6    = GPS quality indicator (0=invalid; 1=GPS fix; 2=Diff. GPS fix)
7    = Number of satellites in use [not those in view]
8    = Horizontal dilution of position
9    = Antenna altitude above/below mean sea level (geoid)
10   = Meters  (Antenna height unit)
11   = Geoidal separation (Diff. between WGS-84 earth ellipsoid and
       mean sea level.  -=geoid is below WGS-84 ellipsoid)
12   = Meters  (Units of geoidal separation)
13   = Age in seconds since last update from diff. reference station
14   = Diff. reference station ID#
15   = Checksum

$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39
    Where:
        GSA Satellite status
        A Auto selection of 2D or 3D fix (M = manual)
        3 3D fix - values include: 1 = no fix
        2 = 2D fix
        3 = 3D fix
        04,05... PRNs of satellites used for fix (space for 12)
        2.5 PDOP (dilution of precision)
        1.3 Horizontal dilution of precision (HDOP)
        2.1 Vertical dilution of precision (VDOP)
        *39 the checksum data, always begins with *

*/


Gps::Gps()
{
    this->gpsParser = new TinyGPS();
    Serial.begin(GPS_SERIAL_BAUD_RATE);
}

void Gps::tick()
{
    if (millis() - this->lastTimeGpsWasTicked < 1000) {
        return;
    }
    this->lastTimeGpsWasTicked = millis();

    bool dataIsAvailable = false;

    while (Serial.available())
    {
        if (this->gpsParser->encode(Serial.read())) {
            dataIsAvailable = true;
        }
    }

    if (dataIsAvailable) {
        getParserData();
    }
}

void Gps::getParserData()
{
    this->gpsParser->f_get_position(&this->latitude, &this->longitude, &this->gpsFixAge);
    this->speed = this->gpsParser->f_speed_kmph();
    this->altitude = this->gpsParser->f_altitude() / 100;
    this->heading = this->gpsParser->f_course();
}

bool Gps::isAvailable()
{
    return gpsHasFreshData() && isValidData();
}

bool Gps::gpsHasFreshData()
{
    return this->gpsFixAge == this->gpsParser->GPS_INVALID_FIX_TIME
        || this->gpsFixAge < 3000;
}

bool Gps::isValidData()
{
    return this->latitude != this->gpsParser->GPS_INVALID_ANGLE 
        && this->longitude != this->gpsParser->GPS_INVALID_ANGLE;
}

float Gps::getLatitude()
{
    return this->latitude;
}

float Gps::getLongitude()
{
    return this->longitude;
}

float Gps::getSpeed()
{
    return this->speed;
}

float Gps::getAltitude()
{
    return this->altitude;
}
