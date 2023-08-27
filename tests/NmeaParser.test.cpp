/*
    Use this command to run the test:
    g++ -c -w ../src/NmeaParser/NmeaParser.cpp NmeaParser.test.cpp && g++ -o NmeaParser.test NmeaParser.o NmeaParser.test.o && ./NmeaParser.test
*/
#include <iostream>
#include <string.h>
#include "../src/NmeaParser/NmeaParser.h"

using namespace std;

void test_tiny_gps()
{
    NmeaParser gpsParser;

    const char Gpgga[] = "$GPGGA,232000,2358.439,S,04618.474,W,1,08,0.9,545.4,M,46.9,M,,*4A\r\n";

    bool dataIsAvailable = false;
    for(int i = 0; i <= strlen(Gpgga); i++) {
        dataIsAvailable = gpsParser.encode(Gpgga[i], 1000);
        if (dataIsAvailable) {
            break;
        }
    };
    
    printf("gpsParser.getLatitude(): %.6f\n", gpsParser.getLatitude());
    printf("gpsParser.getLongitude(): %.6f\n", gpsParser.getLongitude());
    cout << "gpsParser.getNumSats(): " << gpsParser.getNumSats() << endl;

    // if (
    //     (int) gps.getVario() == 83
    // ) {
    //     cout << "\x1b[41m" << "test_tiny_gps OK" << "\x1b[0m" << endl;
    // } else {
    //     cout << "\x1b[42m" << "test_tiny_gps FAIL" << "\x1b[0m"  << endl;
    // }
}

int main( int argc, char *argv[], char *envp[] )
{
    test_tiny_gps();

    return 0;
}
