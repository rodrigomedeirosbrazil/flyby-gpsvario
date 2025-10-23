#include <time.h>
#include "Screen.h"
#include "../defines.h"
#include "../helpers/helpers.h"
#include "../globals.h"

Screen::Screen()
{
}

void Screen::begin()
{
    #ifdef FLYBY_GPS_VARIO
    display.setI2CAddress(0x3F * 2);
    #endif

    display.begin();
    systemStartTime = millis();
}

void Screen::draw()
{
    if (millis() - this->lastTimeScreenWasDrawn < 1000) {
        return;
    }
    this->lastTimeScreenWasDrawn = millis();

    this->screenSelected = InfoScreen;

    if (gps.isAvailable()) {
        this->screenSelected = GpsScreen;
    }

    if (isInfoScreenTimeoutExpired()) {
        this->screenSelected = GpsScreen;
    }

    display.firstPage();
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
    } while (display.nextPage());
}

void Screen::drawGpsScreen()
{
    compass.draw();

    drawInfoBox("ALT", (int) variometer.getAltitude(), "m", 0, barometer.isAvailable());
    drawInfoBox("VAR", variometer.getVario(), "m/s", 1, barometer.isAvailable());
    drawInfoBox("SPD", (int) gps.getSpeed(), "km/h", 2, gps.isAvailable());

    if (gps.isAvailable()) {
        drawGpsAltitudeBox();
    }

    if (wind.isAvailable()) {
        drawWindSpeedBox();
    }

    if (flightCpu.getFlightTime() > 0) {
        display.setFont(SMALL_FONT);
        display.setCursor(54, 64);

        unsigned int hours = flightCpu.getFlightTime() / 3600;
        unsigned int minutes = (flightCpu.getFlightTime() % 3600) / 60;
        display.printf("%01d:%02d", hours, minutes);
    }
}

void Screen::drawInfoScreen()
{
    display.setFont(SMALL_FONT);

    display.setCursor(0, 8);
    barometer.isAvailable()
        ?   display.printf("Pre:%ld", variometer.getPressure())
        :   display.print("Pre: N/A");

    display.setCursor(0, 16);
    barometer.isAvailable()
        ?   display.printf("Alt:%.0f", variometer.getAltitude())
        :   display.print("Alt: N/A");

    display.setCursor(0, 24);
    barometer.isAvailable()
        ?   display.printf("Var:%.1f", variometer.getVario())
        :   display.print("Var: N/A");

    display.setCursor(0, 32);
    display.printf("QNH:%ld", variometer.getQnh());

    display.setCursor(0, 40);
    barometer.isAvailable()
        ?   display.printf("Tmp:%.1f", barometer.getTemperature())
        :   display.print("Tmp: N/A");

    display.setCursor(0, 48);
    display.printf("TMZ: %d", TIMEZONE);

    if (gps.isAvailable()) {
        unsigned long unixtime = convertDateAndTimeEpochTime(gps.getDate(), gps.getTime());

        time_t t = unixtime - (TIMEZONE * 3600);
        struct tm *timestamp = gmtime(&t);

        display.setCursor(0, 56);
        display.printf("%04d-%02d-%02d", timestamp->tm_year + 1900, timestamp->tm_mon + 1, timestamp->tm_mday);

        display.setCursor(0, 64);
        display.printf("%02d:%02d:%02d", timestamp->tm_hour, timestamp->tm_min, timestamp->tm_sec);
    }

    display.setCursor(64, 8);
    display.printf("Lat:%.6f", gps.getLatitude());

    display.setCursor(64, 16);
    display.printf("Lon:%.6f", gps.getLongitude());

    display.setCursor(64, 24);
    display.printf("Spd:%.1f", gps.getSpeed());

    display.setCursor(64, 32);
    display.printf("Hed:%.0f", gps.getHeading());

    display.setCursor(64, 40);
    display.printf("PDP:%ld", gps.getPdop());

    display.setCursor(64, 48);
    display.printf("VDP:%ld", gps.getVdop());

    display.setCursor(64, 56);
    display.printf("Sat:%d", gps.getSatellites());

    display.setCursor(64, 64);
    display.printf("Alt:%.0f", gps.getAltitude());

    display.setCursor(123, 64);
    display.print(spinner[spinnerIndex]);
    if (spinnerIndex == 3) {
        spinnerIndex = 0;
    } else {
        spinnerIndex++;
    }
}

void Screen::drawInfoBox(const char* label, char *value, const char* unit, uint8_t offset, bool isAvailable)
{
    uint8_t x = 74;
    uint8_t y_base = offset * INFOBOX_HEIGHT;

    display.setFont(SMALL_FONT);
    display.drawStr(x + 2, y_base + 5, label);

    display.setFont(BIG_FONT);
    display.drawStr(x, y_base + 17, isAvailable ? value : (char *) this->notAvailableText);

    display.setFont(MEDIUM_FONT);
    display.drawStr(x + 49, y_base + 22, unit);
}

void Screen::drawInfoBox(const char* label, int value, const char* unit, uint8_t offset, bool isAvailable)
{
    char buffer[10];
    sprintf(buffer, "%d", value);
    drawInfoBox(label, buffer, unit, offset, isAvailable);
}

void Screen::drawInfoBox(const char* label, long value, const char* unit, uint8_t offset, bool isAvailable)
{
    char buffer[10];
    sprintf(buffer, "%ld", value);
    drawInfoBox(label, buffer, unit, offset, isAvailable);
}

void Screen::drawInfoBox(const char* label, float value, const char* unit, uint8_t offset, bool isAvailable)
{
    char buffer[10];
    dtostrf(value, 2, 1, buffer);
    drawInfoBox(label, buffer, unit, offset, isAvailable);
}

bool Screen::isInfoScreenTimeoutExpired()
{
    return (millis() - systemStartTime) >= INFO_SCREEN_TIMEOUT;
}

void Screen::drawWindSpeedBox()
{
    display.setFont(SMALL_FONT);
    display.printRight("wind:", 48, 62);
    display.setCursor(69, 62);
    display.printf("%.0fkmh", wind.getSpeed());
    display.drawFrame(46, 55, 44, 9);
}

void Screen::drawGpsAltitudeBox()
{
    display.drawFrame(54, 0, 20, 15);

    display.setFont(SMALL_FONT);
    display.drawStr(59, 7, "GPS");

    display.setCursor(56, 13);
    display.printf("%.0f", gps.getAltitude());
}