#include <U8g2lib.h>
#include "src/defines.h"
#include "src/helper/helper.h"
#include "src/Compass/Compass.h"
#include "src/Variometer/Variometer.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0);

unsigned int degree = 0;
unsigned int altitude = 100;
unsigned int speed = 45;
char vario = 0;

Compass compass(25, 25, 25);
Variometer variometer;

void setup(void) {
  display.begin();
}

void loop(void) {
  variometer.tick();
  display.firstPage();
  do {
    compass.draw(degree);
    drawInfoBox(altitude, "m", 64, 0);
    drawInfoBox(speed, "km/h", 64, 20);
    drawInfoBox(vario, "m/s", 64, 40);
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

  vario = vario > 5
    ? -5
    : vario + 1;
}
