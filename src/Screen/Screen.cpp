#include "Screen.h"
#include "../defines.h"
#include "../helper/helper.h"

Screen::Screen() : compass(25, 25, 25)
{
}

void Screen::draw()
{
    if (millis() - this->lastTimeScreenWasDrawn < 1000) {
        return;
    }

    this->lastTimeScreenWasDrawn = millis();

    display.firstPage();
    do {
        switch (this->screenSelected)
        {
            case GPS_SCREEN:
                drawGpsScreen();
                break;
            
            default:
                break;
        }
    } while (display.nextPage());

    #ifdef DEMO
        this->degree = this->degree >= 360 
            ? 0
            : this->degree + 5;
    
        this->altitude = this->altitude > 2000
            ? 0
            : this->altitude + 20;

        this->speed = this->speed > 60
            ? 0
            : this->speed + 5;

        this->vario = this->vario > 5
            ? -5
            : this->vario + .2;
    #endif
}

void Screen::drawGpsScreen()
{
    compass.draw(this->degree);
    drawInfoBox(this->altitude, "m", 64, 0);
    drawInfoBox(this->speed, "km/h", 64, 20);
    drawInfoBox(this->vario, "m/s", 64, 40);
}

void Screen::setDegree(unsigned int degree)
{
    this->degree = degree;
}

void Screen::setAltitude(unsigned int altitude)
{
    this->altitude = altitude;
}

void Screen::setSpeed(unsigned int speed)
{
    this->speed = speed;
}

void Screen::setVario(float vario)
{
    this->vario = vario;
}