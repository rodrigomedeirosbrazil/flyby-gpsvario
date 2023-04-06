#include <HardwareSerial.h>
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
    #ifndef NO_GPS
    serial2 = new HardwareSerial(2);
    serial2->begin(GPS_BAUD_RATE, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    #endif
}

void Gps::tick()
{
    if (millis() - this->lastTimeGpsWasTicked < 1000) {
        return;
    }
    this->lastTimeGpsWasTicked = millis();

    bool dataIsAvailable = false;

    #ifndef NO_GPS
    while (serial2->available())
    {
        char c = serial2->read();
        if (this->gpsParser->encode(c)) {
            dataIsAvailable = true;
        }
    }
    #endif
    
    #ifdef NO_GPS
    char GPGGA[] = "$GPGGA,232000,2358.439,S,04618.474,W,1,08,0.9,545.4,M,46.9,M,,*4A";
    char GPGSA[] = "$GPGSA,A,3,04,05,,09,12,,,24,,,,,2.5,1.3,2.1*39";
    char GPRMC[] = "$GPRMC,232000,A,2358.439,S,04618.474,W,022.4,090.0,050616,003.1,W*6D";
    dataIsAvailable = true;

    for(int i = 0; i < strlen(GPGGA); i++) {
        this->gpsParser->encode(GPGGA[i]);
    }
    this->gpsParser->encode('\r');
    this->gpsParser->encode('\n');

    for(int i = 0; i < strlen(GPGSA); i++) {
        this->gpsParser->encode(GPGSA[i]);
    }
    this->gpsParser->encode('\r');
    this->gpsParser->encode('\n');

    for(int i = 0; i < strlen(GPRMC); i++) {
        this->gpsParser->encode(GPRMC[i]);
    }
    this->gpsParser->encode('\r');
    this->gpsParser->encode('\n');
    #endif

    if (dataIsAvailable) {
        getParserData();
    }
}

void Gps::getParserData()
{
    this->gpsParser->f_get_position(&this->latitude, &this->longitude, &this->gpsFixAge);
    this->speed = this->gpsParser->f_speed_kmph();
    this->altitude = this->gpsParser->f_altitude();
    this->heading = this->gpsParser->f_course();
    this->hdop = this->gpsParser->hdop();
    this->vdop = this->gpsParser->vdop();
    this->satellites = this->gpsParser->satellites();
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

float Gps::getHeading()
{
    return this->heading;
}

unsigned long Gps::getHdop()
{
    return this->hdop;
}

unsigned long Gps::getVdop()
{
    return this->vdop;
}

unsigned short Gps::getSatellites()
{
    return this->satellites;
}

void Gps::getDateTime(
    int *year, 
    byte *month, 
    byte *day, 
    byte *hour, 
    byte *minute, 
    byte *second
) {
    this->gpsParser->crack_datetime(year, month, day, hour, minute, second, nullptr);
}
