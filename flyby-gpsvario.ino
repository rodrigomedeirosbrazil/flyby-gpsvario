#include <U8g2lib.h>
#include "src/defines.h"
#include "src/compass/compass.h"
#include "src/helper/helper.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0);

unsigned int degree = 0;
unsigned int altitude = 100;
unsigned int speed = 45;
char variometer = 0;

void setup(void) {
  display.begin();
}

void loop(void) {
  display.firstPage();
  do {
    drawCompass();
    drawInfoBox(altitude, "m", 64, 0);
    drawInfoBox(speed, "km/h", 64, 20);
    drawInfoBox(variometer, "m/s", 64, 40);
  } while (display.nextPage());

  delay(1000);

  degree = degree >= 360 
    ? 0
    : degree + 5;
  
  altitude = altitude > 2000
    ? 0
    : altitude + 20;

  speed = speed > 60
    ? 0
    : speed + 5;

  variometer = variometer > 5
    ? -5
    : variometer + 1;
}
