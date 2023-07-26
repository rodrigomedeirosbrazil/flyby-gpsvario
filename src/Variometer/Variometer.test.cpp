/*
    Use this command to run the test:
    g++ -c -w Variometer.cpp Variometer.test.cpp && g++ -o Variometer.test Variometer.o Variometer.test.o && ./Variometer.test
*/
#include <iostream>
#include <string.h>
#include "Variometer.h"

using namespace std;

void test_vario()
{
    Variometer vario;

    for(int i = 0; i <= 60; i++) {
        vario.tick(101325 - i, i);
    };
    
    // cout << "Vario: " << (int) vario.getVario() << endl;
    // cout << "Altitude: " << (int) vario.getAltitude() << endl;

    if (
        (int) vario.getVario() == 83
    ) {
        cout << "\x1b[40m" << "test_vario OK" << "\x1b[0m" << endl;
    } else {
        cout << "\x1b[40m" << "test_vario FAIL" << "\x1b[0m"  << endl;
    }
}

void test_vario_with_qnh_change()
{
    Variometer vario;

    vario.setQnh(101325);

    for(int i = 0; i <= 60; i++) {
        vario.tick(101325 - i, i);
        if (i == 30) {
            vario.setQnh(102100);
        }
    };
    
    // cout << "Vario: " << (int) vario.getVario() << endl;
    // cout << "Altitude: " << (int) vario.getAltitude() << endl;

    if (
        (int) vario.getVario() == 83
    ) {
        cout << "\x1b[40m" << "test_vario_with_qnh_change OK" << "\x1b[0m" << endl;
    } else {
        cout << "\x1b[40m" << "test_vario_with_qnh_change FAIL" << "\x1b[0m"  << endl;
    }
}

int main( int argc, char *argv[], char *envp[] )
{
    test_vario();
    test_vario_with_qnh_change();

    return 0;
}
