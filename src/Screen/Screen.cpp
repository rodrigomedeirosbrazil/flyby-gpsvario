#include "Screen.h"
#include "../defines.h"

Screen::Screen()
{
    #ifdef WOKWI
    this->display = new Display(U8G2_R0);
    #endif

    #ifdef SMARTVARIO
    this->display = new Display(
        U8G2_R0, 
        LCD_CLOCK_PIN,
        LCD_DATA_PIN,
        LCD_CS_PIN, 
        LCD_DC_PIN, 
        LCD_RESET_PIN
    );
    #endif

    this->compass = new Compass(this->display, 25, 25, 25);
}

void Screen::begin()
{
    this->display->begin();
    this->display->setContrast(SCREEN_CONTRAST);
}

void Screen::draw()
{
    if (millis() - this->lastTimeScreenWasDrawn < 1000) {
        return;
    }

    this->lastTimeScreenWasDrawn = millis();

    this->display->firstPage();
    do {
        switch (this->screenSelected)
        {
            case GPS_SCREEN:
                drawGpsScreen();
                break;
            
            default:
                break;
        }
    } while (this->display->nextPage());

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
    this->compass->draw(this->degree);
    drawInfoBox((int) this->altitude, "m", 64, 0);
    drawInfoBox((int) this->speed, "km/h", 64, 20);
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

void Screen::drawInfoBox (char *value, char* unit, uint8_t x, uint8_t y)
{
    this->display->setFont(BIG_FONT);

    this->display->printRight(
        value,
        x + INFOBOX_WIDTH - SMALL_FONT_WIDTH,
        y + BIG_FONT_HEIGHT - 5);

    this->display->setFont(SMALL_FONT);

    this->display->printRight(
        unit,
        x + INFOBOX_WIDTH,
        y + INFOBOX_HEIGHT);
}

void Screen::drawInfoBox (int value, char* unit, uint8_t x, uint8_t y)
{
    char buffer[6];
    sprintf(buffer, "%d", value);
    drawInfoBox(buffer, unit, x, y);
}

void Screen::drawInfoBox (float value, char* unit, uint8_t x, uint8_t y)
{
    char buffer[6]; 
    dtostrf(value, 2, 1, buffer);
    drawInfoBox(buffer, unit, x, y);
}