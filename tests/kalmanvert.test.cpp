/*
    Use this command to run the test:
    g++ -c -w ../src/kalmanvert/kalmanvert.cpp kalmanvert.test.cpp && g++ -o kalmanvert.test kalmanvert.o kalmanvert.test.o && ./kalmanvert.test
*/
#include <iostream>
#include <string.h>
#include "../src/kalmanvert/kalmanvert.h"

using namespace std;

void test_kalman_filter()
{
    kalmanvert filter;

    filter.init(
        0, // startp firstAlti
        0.0, // starta
        0.1, // POSITION_MEASURE_STANDARD_DEVIATION
        0.3, // ACCELERATION_MEASURE_STANDARD_DEVIATION
        0 // timestamp
    );

    for(int i = 0; i <= 1000; i++) {
        filter.update(
            i, // altitude
            0, // aceleration from accelerometer
            i + 10 // timestamp
        );
    };
    
    // cout << "Vario speed: " << (int) filter.getVelocity() << endl;
    // cout << "Vario position: " << (int) filter.getCalibratedPosition() << endl;

    if (
        (int) filter.getVelocity() == 698 &&
        (int) filter.getCalibratedPosition() == 556
    ) {
        cout << "\x1b[42m" << "test_kalman_filter OK" << "\x1b[0m" << endl;
    } else {
        cout << "\x1b[41m" << "test_kalman_filter FAIL" << "\x1b[0m"  << endl;
    }
}

int main( int argc, char *argv[], char *envp[] )
{
    test_kalman_filter();

    return 0;
}
