#include <U8g2lib.h>
#include "src/compass/compass.h"
#include "src/helper/helper.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0);

unsigned int degree = 0;
unsigned int altitude = 100;
unsigned int speed = 45;

unsigned char compassX=25;
unsigned char compassY=25;
unsigned char compassSize=25;

void setup(void) {
  display.begin();
}

void loop(void) {
  display.firstPage();
  do {
    drawCompass();
    drawAltitude();
  } while (display.nextPage());
  delay(100);
  degree = degree >= 360 
    ? 0
    : degree + 5;
  
  altitude = altitude > 2000
    ? 0
    : altitude + 20;

  speed = speed > 60
    ? 0
    : speed + 5;
}

void drawAltitude()
{
  display.setFont(u8g2_font_10x20_tr);
  printNumberRight(altitude, display.getDisplayWidth(), display.getMaxCharHeight());
  display.setFont(u8g_font_5x7);
  display.setCursor(display.getDisplayWidth() - display.getMaxCharWidth(), display.getMaxCharHeight());
  display.print("m");
}
