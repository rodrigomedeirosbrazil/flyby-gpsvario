/*
    Use this command to run the test:
    g++ -c -w ../src/Variometer/Variometer.cpp Variometer.test.cpp && g++ -o Variometer.test Variometer.o Variometer.test.o && ./Variometer.test
*/
#include <iostream>
#include <string.h>
#include "../src/Variometer/Variometer.h"

using namespace std;

void test_vario()
{
    Variometer vario;

    for(int i = 0; i <= 60; i++) {
        vario.tick(101325 - (i * 100), i * 10);
    };

    float varioValue = vario.getVario();

    if (varioValue >= 0.8 && varioValue <= 0.9) {
        cout << "\x1b[40m" << "test_vario OK (vario: " << varioValue << " m/s)" << "\x1b[0m" << endl;
    } else {
        cout << "\x1b[41m" << "test_vario FAIL (vario: " << varioValue << " m/s, expected ~0.83 m/s)" << "\x1b[0m"  << endl;
    }
}

void test_vario_with_qnh_change()
{
    Variometer vario;

    vario.setQnh(101325);

    for(int i = 0; i <= 60; i++) {
        vario.tick(101325 - (i * 100), i * 10);
        if (i == 30) {
            vario.setQnh(102100);
        }
    };

    float varioValue = vario.getVario();

    if (varioValue >= 0.8 && varioValue <= 0.9) {
        cout << "\x1b[40m" << "test_vario_with_qnh_change OK (vario: " << varioValue << " m/s)" << "\x1b[0m" << endl;
    } else {
        cout << "\x1b[41m" << "test_vario_with_qnh_change FAIL (vario: " << varioValue << " m/s, expected ~0.83 m/s)" << "\x1b[0m"  << endl;
    }
}

int main( int argc, char *argv[], char *envp[] )
{
    test_vario();
    test_vario_with_qnh_change();

    return 0;
}
