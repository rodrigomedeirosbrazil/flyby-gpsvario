/*
    Use this command to run the test:
    g++ -c -w ../src/KalmanFilter4d/kalmanfilter4d.cpp kalmanfilter4d.test.cpp && g++ -o kalmanfilter4d.test kalmanfilter4d.o kalmanfilter4d.test.o && ./kalmanfilter4d.test
*/
#include <iostream>
#include <string.h>
#include "../src/KalmanFilter4d/kalmanfilter4d.h"

using namespace std;

void test_kalman_filter()
{
    float KFAltitudeCm, KFClimbrateCps;

    kalmanFilter4d_configure(0, 0, 1.0f, 0.0f, 0.0f);

    
    for(int i = 1; i <= 11; i++) {
        kalmanFilter4d_predict(1);
        kalmanFilter4d_update(i * 100, 0, (float*)&KFAltitudeCm, (float*)&KFClimbrateCps);
    };
    
    int expected_KFClimbrateCps = 192;
    int expected_KFAltitudeCm = 1127;

    if (
        (int) KFClimbrateCps == expected_KFClimbrateCps &&
        (int) KFAltitudeCm == expected_KFAltitudeCm
    ) {
        cout << "\x1b[42m" << 
        "test_kalman_filter OK - expected KFClimbrateCps == " << expected_KFClimbrateCps << 
        " && KFAltitudeCm == " << expected_KFAltitudeCm << 
        "\x1b[0m" << endl;
    } else {
        cout << "\x1b[41m" << 
        "test_kalman_filter FAIL - expected KFClimbrateCps == " << expected_KFClimbrateCps << " encountered " << (int) KFClimbrateCps <<
        " && KFAltitudeCm == " << expected_KFAltitudeCm << " encountered " << (int) KFAltitudeCm <<
        "\x1b[0m" << endl;
    }
}

int main( int argc, char *argv[], char *envp[] )
{
    test_kalman_filter();

    return 0;
}