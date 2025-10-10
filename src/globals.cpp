#include "globals.h"
#include "defines.h"

Barometer barometer;
Variometer variometer;
Beep beep(SPEAKER_PIN);
Gps gps;
Wind wind;

#ifdef FLYBY_GPS_VARIO
Display display(U8G2_R2, LCD_CLOCK_PIN, LCD_DATA_PIN, U8X8_PIN_NONE);
#endif

#ifdef WOKWI
Display display(U8G2_R0);
#endif

Compass compass(25, 25, 25);
Screen screen;
FlightCpu flightCpu;

