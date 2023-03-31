#include "Screen.h"
#include "../defines.h"

Screen::Screen(Variometer *variometer)
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
    this->variometer = variometer;
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

            case INFO_SCREEN:
                drawInfoScreen();
                break;

            default:
                break;
        }
    } while (this->display->nextPage());
}

void Screen::drawGpsScreen()
{
    this->compass->draw(0);
    drawInfoBox(this->variometer->getAltitude(), "m", 64, 0, this->variometer->isAvailable());
    drawInfoBox(nullptr, "km/h", 64, 20, false);
    drawInfoBox(this->variometer->getVario(), "m/s", 64, 40, this->variometer->isAvailable());
}

void Screen::drawInfoScreen()
{
    drawInfoBox(this->variometer->getAltitude(), "m", 0, 0, this->variometer->isAvailable());
    drawInfoBox(nullptr, "km/h", 0, 20, false);
    drawInfoBox(this->variometer->getVario(), "m/s", 0, 40, this->variometer->isAvailable());

    drawInfoBox(this->variometer->getPressure(), "Pa", 64, 0, this->variometer->isAvailable());
    drawInfoBox(this->variometer->getTemperature(), "C", 64, 20, this->variometer->isAvailable());
    drawInfoBox(this->variometer->getQnh(), "Pa", 64, 40, true);
}

void Screen::drawInfoBox (char *value, char* unit, uint8_t x, uint8_t y, bool isAvailable)
{
    this->display->setFont(BIG_FONT);

    this->display->printRight(
        isAvailable 
            ? value 
            : (char *) this->notAvailableText,
        x + INFOBOX_WIDTH - SMALL_FONT_WIDTH,
        y + BIG_FONT_HEIGHT - 5);

    this->display->setFont(SMALL_FONT);

    this->display->printRight(
        unit,
        x + INFOBOX_WIDTH,
        y + INFOBOX_HEIGHT);
}

void Screen::drawInfoBox (int value, char* unit, uint8_t x, uint8_t y, bool isAvailable)
{
    char buffer[10];
    sprintf(buffer, "%d", value);
    drawInfoBox(buffer, unit, x, y, isAvailable);
}

void Screen::drawInfoBox (long value, char* unit, uint8_t x, uint8_t y, bool isAvailable)
{
    char buffer[10];
    sprintf(buffer, "%ld", value);
    drawInfoBox(buffer, unit, x, y, isAvailable);
}

void Screen::drawInfoBox (float value, char* unit, uint8_t x, uint8_t y, bool isAvailable)
{
    char buffer[10]; 
    dtostrf(value, 2, 1, buffer);
    drawInfoBox(buffer, unit, x, y, isAvailable);
}