/*
    Use this command to run the test:
    g++ -c -w ../src/NmeaParser/NmeaParser.cpp NmeaParser.test.cpp && g++ -o NmeaParser.test NmeaParser.o NmeaParser.test.o && ./NmeaParser.test
*/
#include <iostream>
#include <string.h>
#include "../src/NmeaParser/NmeaParser.h"

using namespace std;

void test_nmea_parser()
{
    NmeaParser gpsParser;

    const char stream[] = "$GPGGA,232000,2358.439,S,04618.474,W,1,08,0.9,545.4,M,46.9,M,,*4A\r\n$GPRMC,232000,A,2358.439,S,04618.474,W,022.4,090.0,050616,003.1,W*6D\r\n";

    for(int i = 0; i <= strlen(stream); i++) {
        gpsParser.encode(stream[i], 1000);
    };

    unsigned long expected_time = 23200000;
    if (
        gpsParser.getTime()
        != expected_time
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_time: " << expected_time << " encountered " << gpsParser.getTime() <<
        "\x1b[0m"  << endl;
        return;
    }

    int expected_latitude = -23973984;
    if (
        (int) (gpsParser.getLatitude() * 1000000) 
        != expected_latitude
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_latitude: " << expected_latitude << " encountered " << (int) (gpsParser.getLatitude() * 1000000) <<
        "\x1b[0m"  << endl;
        return;
    }

    int expected_longitude = -46307900;
    if (
        (int) (gpsParser.getLongitude() * 1000000) 
        != expected_longitude
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_longitude: " << expected_longitude << " encountered " << (int) (gpsParser.getLongitude() * 1000000) <<
        "\x1b[0m"  << endl;
        return;
    }

    int expected_num_sats = 8;
    if (
        gpsParser.getNumSats()
        != expected_num_sats
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_num_sats: " << expected_num_sats << " encountered " << gpsParser.getNumSats() <<
        "\x1b[0m"  << endl;
        return;
    }

    unsigned long expected_hdop = 90;
    if (
        gpsParser.getHdop()
        != expected_hdop
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_hdop: " << expected_hdop << " encountered " << gpsParser.getHdop() <<
        "\x1b[0m"  << endl;
        return;
    }

    long expected_altitude = 545;
    if (
        gpsParser.getAltitudeMeters()
        != expected_altitude
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_altitude: " << expected_altitude << " encountered " << gpsParser.getAltitudeMeters() <<
        "\x1b[0m"  << endl;
        return;
    }

    unsigned long expected_speed = 22;
    if (
        gpsParser.getSpeedKnots()
        != expected_speed
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_speed: " << expected_speed << " encountered " << gpsParser.getSpeedKnots() <<
        "\x1b[0m"  << endl;
        return;
    }

    long expected_course = 90;
    if (
        gpsParser.getCourseDegrees()
        != expected_course
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_course: " << expected_course << " encountered " << gpsParser.getCourseDegrees() <<
        "\x1b[0m"  << endl;
        return;
    }

    unsigned long expected_date = 50616;
    if (
        gpsParser.getDate()
        != expected_date
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "expected_date: " << expected_date << " encountered " << gpsParser.getDate() <<
        "\x1b[0m"  << endl;
        return;
    }

    struct tm datetime;

    if (gpsParser.getDatetime(&datetime) == false) {
      cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "datetime fail" <<
        "\x1b[0m"  << endl;
        return;
    }

    int expected_year = 116;
    int expected_month = 6;
    int expected_day = 5;
    int expected_hour = 23;
    int expected_minute = 20;
    int expected_second = 0;

    if (
        datetime.tm_year != expected_year
        || datetime.tm_mon != expected_month
        || datetime.tm_mday != expected_day
        || datetime.tm_hour != expected_hour
        || datetime.tm_min != expected_minute
        || datetime.tm_sec != expected_second
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " << endl <<
        "expected_year: " << expected_year << " encountered " << datetime.tm_year << endl <<
        "expected_month: " << expected_month << " encountered " << datetime.tm_mon << endl <<
        "expected_day: " << expected_day << " encountered " << datetime.tm_mday << endl <<
        "expected_hour: " << expected_hour << " encountered " << datetime.tm_hour << endl <<
        "expected_minute: " << expected_minute << " encountered " << datetime.tm_min << endl <<
        "expected_second: " << expected_second << " encountered " << datetime.tm_sec <<
        "\x1b[0m"  << endl;
        return;
    }

    if (gpsParser.getDatetime(&datetime, -3) == false) {
      cout << "\x1b[41m" << 
        "test_nmea_parser FAIL " <<
        "datetime with timezone fail" <<
        "\x1b[0m"  << endl;
        return;
    }

    expected_year = 116;
    expected_month = 6;
    expected_day = 5;
    expected_hour = 20;
    expected_minute = 20;
    expected_second = 0;

    if (
        datetime.tm_year != expected_year
        || datetime.tm_mon != expected_month
        || datetime.tm_mday != expected_day
        || datetime.tm_hour != expected_hour
        || datetime.tm_min != expected_minute
        || datetime.tm_sec != expected_second
    ) {
        cout << "\x1b[41m" << 
        "test_nmea_parser datetimeWithTimezone FAIL " << endl <<
        "expected_year: " << expected_year << " encountered " << datetime.tm_year << endl <<
        "expected_month: " << expected_month << " encountered " << datetime.tm_mon << endl <<
        "expected_day: " << expected_day << " encountered " << datetime.tm_mday << endl <<
        "expected_hour: " << expected_hour << " encountered " << datetime.tm_hour << endl <<
        "expected_minute: " << expected_minute << " encountered " << datetime.tm_min << endl <<
        "expected_second: " << expected_second << " encountered " << datetime.tm_sec <<
        "\x1b[0m"  << endl;
        return;
    }

    cout << "\x1b[42m" << "test_nmea_parser OK" << "\x1b[0m" << endl;
}

int main( int argc, char *argv[], char *envp[] )
{
    test_nmea_parser();

    return 0;
}
