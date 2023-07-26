#include <time.h>
#include "Screen.h"
#include "../defines.h"
#include "../helpers/helpers.h"

Screen::Screen(FlightCpu *flightCpu)
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

    this->flightCpu = flightCpu;
    this->compass = new Compass(this->display, 25, 25, 25);
}

void Screen::begin()
{
    #ifdef FLYBY_GPS_VARIO
    this->display->setI2CAddress(0x3F * 2);
    #endif

    this->display->begin();
    // this->display->setContrast(SCREEN_CONTRAST);
}

void Screen::draw()
{
    if (millis() - this->lastTimeScreenWasDrawn < 1000) {
        return;
    }
    this->lastTimeScreenWasDrawn = millis();

    this->screenSelected = this->flightCpu->getGps()->isAvailable() 
        ? GpsScreen 
        : InfoScreen;

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
    this->compass->setHeading(this->flightCpu->getGps()->getHeading());
    this->compass->setWindDirection(this->flightCpu->getWind()->getDirection());
    this->compass->setWindAvailabilty(this->flightCpu->getWind()->isAvailable());
    this->compass->draw();

    drawInfoBox((int) this->flightCpu->getVariometer()->getAltitude(), "m", 64, 0, this->flightCpu->getBarometer()->isAvailable());
    drawInfoBox((int) this->flightCpu->getGps()->getSpeed(), "km/h", 64, 20, this->flightCpu->getGps()->isAvailable());
    drawInfoBox(this->flightCpu->getVariometer()->getVario(), "m/s", 64, 40, this->flightCpu->getBarometer()->isAvailable());


    this->display->setFont(SMALL_FONT);
    this->display->setCursor(54, 8);
    this->display->printf("%.0fm", this->flightCpu->getGps()->getAltitude());

    this->display->setCursor(54, 32);
    this->display->printf("%.0fkmh", this->flightCpu->getWind()->getSpeed());

    this->display->setCursor(54, 40);
    this->display->printf("%ld", this->flightCpu->getWind()->getDirection());

    this->display->setCursor(54, 48);
    this->display->printf("%ld", this->flightCpu->getGps()->getPdop());

    this->display->setCursor(54, 56);
    this->display->printf("%ld", this->flightCpu->getGps()->getVdop());

    if (this->flightCpu && this->flightCpu->getFlightTime() > 0) {
        this->display->setFont(SMALL_FONT);
        this->display->setCursor(54, 64);
        
        unsigned int hours = this->flightCpu->getFlightTime() / 3600;
        unsigned int minutes = (this->flightCpu->getFlightTime() % 3600) / 60;
        this->display->printf("%01d:%02d", hours, minutes);
    }
}

void Screen::drawInfoScreen()
{
    this->display->setFont(SMALL_FONT);

    this->display->setCursor(0, 8);
    this->flightCpu->getBarometer()->isAvailable() 
        ?   this->display->printf("Pre:%ld", this->flightCpu->getVariometer()->getPressure())
        :   this->display->print("Pre: N/A");

    this->display->setCursor(0, 16);
    this->flightCpu->getBarometer()->isAvailable() 
        ?   this->display->printf("Alt:%.0f", this->flightCpu->getVariometer()->getAltitude())
        :   this->display->print("Alt: N/A");

    this->display->setCursor(0, 24);
    this->flightCpu->getBarometer()->isAvailable() 
        ?   this->display->printf("Var:%.1f", this->flightCpu->getVariometer()->getVario())
        :   this->display->print("Var: N/A");

    this->display->setCursor(0, 32);
    this->display->printf("QNH:%ld", this->flightCpu->getVariometer()->getQnh());

    this->display->setCursor(0, 40);
    this->flightCpu->getBarometer()->isAvailable() 
        ?   this->display->printf("Tmp:%.1f", this->flightCpu->getBarometer()->getTemperature())
        :   this->display->print("Tmp: N/A");

    this->display->setCursor(0, 48);
    this->display->printf("TMZ: %d", TIMEZONE);

    if (this->flightCpu->getGps()->isAvailable()) {
        unsigned long unixtime = convertDateAndTimeEpochTime(this->flightCpu->getGps()->getDate(), this->flightCpu->getGps()->getTime());

        time_t t = unixtime - (TIMEZONE * 3600);
        struct tm *timestamp = gmtime(&t);

        this->display->setCursor(0, 56);
        this->display->printf("%04d-%02d-%02d", timestamp->tm_year + 1900, timestamp->tm_mon + 1, timestamp->tm_mday);

        this->display->setCursor(0, 64);
        this->display->printf("%02d:%02d:%02d", timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec);
    }
    

    this->display->setCursor(64, 8);
    this->display->printf("Lat:%.6f", this->flightCpu->getGps()->getLatitude());

    this->display->setCursor(64, 16);
    this->display->printf("Lon:%.6f", this->flightCpu->getGps()->getLongitude());

    this->display->setCursor(64, 24);
    this->display->printf("Spd:%.1f", this->flightCpu->getGps()->getSpeed());

    this->display->setCursor(64, 32);
    this->display->printf("Hed:%.0f", this->flightCpu->getGps()->getHeading());

    this->display->setCursor(64, 40);
    this->display->printf("PDP:%ld", this->flightCpu->getGps()->getPdop());

    this->display->setCursor(64, 48);
    this->display->printf("VDP:%ld", this->flightCpu->getGps()->getVdop());

    this->display->setCursor(64, 56);
    this->display->printf("Sat:%d", this->flightCpu->getGps()->getSatellites());

    this->display->setCursor(64, 64);
    this->display->printf("Alt:%.0f", this->flightCpu->getGps()->getAltitude());

    this->display->setCursor(123, 64);
    this->display->print(spinner[spinnerIndex]);
    if (spinnerIndex == 3) {
        spinnerIndex = 0;
    } else {
        spinnerIndex++;
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
