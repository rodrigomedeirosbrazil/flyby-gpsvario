#include "Screen.h"
#include "../defines.h"

Screen::Screen(Variometer *variometer, Gps *gps)
{
    #ifdef FLYBY_GPS_VARIO
    this->display = new Display(
        U8G2_R2, 
        LCD_CLOCK_PIN,
        LCD_DATA_PIN,
        U8X8_PIN_NONE
    );
    #endif

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
    // #ifdef FLYBY_GPS_VARIO
    this->display->setI2CAddress(0x3F * 2);
    // #endif

    this->display->begin();
    // this->display->setContrast(SCREEN_CONTRAST);
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
            case GpsScreen:
                drawGpsScreen();
                break;

            case InfoScreen:
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
    this->display->setFont(SMALL_FONT);

    this->display->setCursor(0, 8);
    this->variometer->isAvailable() 
        ?   this->display->printf("Pres: %ld", this->variometer->getPressure())
        :   this->display->print("Pres: N/A");

    this->display->setCursor(0, 16);
    this->variometer->isAvailable() 
        ?   this->display->printf("Alti: %d", this->variometer->getAltitude())
        :   this->display->print("Alti: N/A");

    this->display->setCursor(0, 24);
    this->variometer->isAvailable() 
        ?   this->display->printf("Vari: %.1f", this->variometer->getVario())
        :   this->display->print("Vari: N/A");

    this->display->setCursor(0, 32);
    this->display->printf("QNH: %ld", this->variometer->getQnh());

    this->display->setCursor(0, 40);
    this->variometer->isAvailable() 
        ?   this->display->printf("Temp: %.1f", this->variometer->getTemperature())
        :   this->display->print("Temp: N/A");

    this->display->setCursor(64, 8);
    this->gps->isAvailable()
        ?   this->display->printf("Lat: %.6f", this->gps->getLatitude())
        :   this->display->print("Lat: N/A");

    this->display->setCursor(64, 16);
    this->gps->isAvailable() 
        ?   this->display->printf("Lon: %.6f", this->gps->getLongitude())
        :   this->display->print("Lon: N/A");

    this->display->setCursor(64, 24);
    this->gps->isAvailable() 
        ?   this->display->printf("Spd: %.1f", this->gps->getSpeed())
        :   this->display->print("Spd: N/A");

    this->display->setCursor(64, 32);
    this->gps->isAvailable() 
        ?   this->display->printf("Hed: %.0f", this->gps->getHeading())
        :   this->display->print("Hed: N/A");

    this->display->setCursor(64, 40);
    this->gps->isAvailable() 
        ?   this->display->printf("HDOP: %ld", this->gps->getHdop())
        :   this->display->print("HDOP: N/A");

    this->display->setCursor(64, 48);
    this->gps->isAvailable() 
        ?   this->display->printf("VDOP: %ld", this->gps->getVdop())
        :   this->display->print("VDOP: N/A");
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