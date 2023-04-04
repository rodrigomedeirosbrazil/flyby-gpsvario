#include "Screen.h"
#include "../defines.h"

Screen::Screen(Variometer *variometer, Gps *gps)
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
    this->gps = gps;
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
    if (this->variometer->isAvailable()) {
        this->display->setCursor(0, 0);
        this->display->print(this->variometer->getPressure());

        this->display->setCursor(0, 8);
        this->display->print(this->variometer->getAltitude());

        this->display->setCursor(0, 16);
        this->display->print(this->variometer->getVario());

        this->display->setCursor(0, 24);
        this->display->print(this->variometer->getQnh());

        this->display->setCursor(0, 32);
        this->display->print(this->variometer->getTemperature());
    }

    if (this->gps->isAvailable()) {
        this->display->setCursor(64, 0);
        this->display->print(this->gps->getLatitude());

        this->display->setCursor(64, 8);
        this->display->print(this->gps->getLongitude());

        this->display->setCursor(64, 16);
        this->display->print(this->gps->getSpeed());

        this->display->setCursor(64, 24);
        this->display->print(this->gps->getHeading());

        this->display->setCursor(64, 32);
        this->display->print(this->gps->getHdop());

        this->display->setCursor(64, 40);
        this->display->print(this->gps->getVdop());
    }
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