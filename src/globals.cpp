#include "globals.h"
#include "defines.h"
#include "Barometer/Barometer.h"
#include "Variometer/Variometer.h"
#include "Beep/Beep.h"
#include "Gps/Gps.h"
#include "Wind/Wind.h"
#include "Display/Display.h"
#include "compass/compass.h"
#include "Screen/Screen.h"
#include "FlightCpu/FlightCpu.h"

Barometer barometer;
Variometer variometer;
Beep beep(SPEAKER_PIN);
Gps gps;
Wind wind;

#ifdef FLYBY_GPS_VARIO
Display display(U8G2_R2, U8X8_PIN_NONE, LCD_CLOCK_PIN, LCD_DATA_PIN);
#endif

#ifdef WOKWI
Display display(U8G2_R0);
#endif

Compass compass(25, 25, 25);
Screen screen;
FlightCpu flightCpu;

