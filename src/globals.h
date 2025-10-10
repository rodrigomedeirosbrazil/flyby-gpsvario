#ifndef GLOBALS_H
#define GLOBALS_H

#include "Barometer/Barometer.h"
#include "Variometer/Variometer.h"
#include "Beep/Beep.h"
#include "Gps/Gps.h"
#include "Wind/Wind.h"
#include "Display/Display.h"
#include "Compass/Compass.h"
#include "Screen/Screen.h"
#include "FlightCpu/FlightCpu.h"

extern Barometer barometer;
extern Variometer variometer;
extern Beep beep;
extern Gps gps;
extern Wind wind;
extern Display display;
extern Compass compass;
extern Screen screen;
extern FlightCpu flightCpu;

#endif

