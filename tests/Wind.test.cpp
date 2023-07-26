/*
    Use this command to run the test:
    g++ -c -w ../src/Wind/Wind.cpp Wind.test.cpp && g++ -o Wind.test Wind.o Wind.test.o && ./Wind.test
*/
#include <iostream>
#include <string.h>
#include "../src/Wind/Wind.h"

using namespace std;

void test_south_wind()
{
    Wind wind;
    wind.storeSpeed(0, 40, 0);
    wind.storeSpeed(15, 38, 1000);
    wind.storeSpeed(180, 30, 3000);
    // cout << "Wind direction " << wind.getDirection() << endl;
    // cout << "Win speed " << wind.getSpeed() << endl;

    if (
        wind.getDirection() == 180
        && wind.getSpeed() == 10
    ) {
        cout << "test_south_wind OK" << endl;
    } else {
        cout << "test_south_wind FAIL" << endl;
    }
}

void test_east_wind()
{
    Wind wind;
    wind.storeSpeed(260, 45, 0);
    wind.storeSpeed(15, 38, 1000);
    wind.storeSpeed(80, 30, 3000);
    // cout << "Wind direction " << wind.getDirection() << endl;
    // cout << "Win speed " << wind.getSpeed() << endl;

    if (
        wind.getDirection() == 90
        && wind.getSpeed() == 15
    ) {
        cout << "test_east_wind OK" << endl;
    } else {
        cout << "test_east_wind FAIL" << endl;
    }
}

void test_north_wind()
{
    Wind wind;
    wind.storeSpeed(180, 45, 0);
    wind.storeSpeed(15, 38, 1000);
    wind.storeSpeed(0, 30, 3000);
    // cout << "Wind direction " << wind.getDirection() << endl;
    // cout << "Win speed " << wind.getSpeed() << endl;

    if (
        wind.getDirection() == 0
        && wind.getSpeed() == 15
    ) {
        cout << "test_north_wind OK" << endl;
    } else {
        cout << "test_north_wind FAIL" << endl;
    }
}

void test_sse_wind()
{
    Wind wind;
    wind.storeSpeed(335, 45, 0);
    wind.storeSpeed(15, 38, 1000);
    wind.storeSpeed(150, 30, 3000);
    // cout << "Wind direction " << wind.getDirection() << endl;
    // cout << "Win speed " << wind.getSpeed() << endl;

    if (
        wind.getDirection() == 157
        && wind.getSpeed() == 15
    ) {
        cout << "test_sse_wind OK" << endl;
    } else {
        cout << "test_sse_wind FAIL" << endl;
    }
}

int main( int argc, char *argv[], char *envp[] )
{
    test_south_wind();
    test_east_wind();
    test_north_wind();
    test_sse_wind();

    return 0;
}
