#include <U8g2lib.h>
#include "src/compass/compass.h"
#include "src/helper/helper.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0);

#define INFOBOX_WIDTH 64
#define INFOBOX_HEIGHT 20

#define SMALL_FONT u8g_font_5x7
#define SMALL_FONT_WIDTH 5
#define SMALL_FONT_HEIGHT 7

#define BIG_FONT u8g2_font_10x20_tr
#define BIG_FONT_WIDTH 10
#define BIG_FONT_HEIGHT 20

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
    drawAltitude(64, 0);
    drawSpeed(64, 20);
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

void drawAltitude(unsigned int x, unsigned int y)
{
  // display.drawFrame(x, y, INFOBOX_WIDTH, INFOBOX_HEIGHT);

  display.setFont(BIG_FONT);

  printNumberRight(
    altitude, 
    x + INFOBOX_WIDTH - SMALL_FONT_WIDTH, 
    y + BIG_FONT_HEIGHT - 5
  );

  display.setFont(SMALL_FONT);

  printRight(
      "m",
      x + INFOBOX_WIDTH,
      y + INFOBOX_HEIGHT
  );
}

void drawSpeed(unsigned int x, unsigned int y)
{
  // display.drawFrame(x, y, INFOBOX_WIDTH, INFOBOX_HEIGHT);

  display.setFont(BIG_FONT);

  printNumberRight(
      speed,
      x + INFOBOX_WIDTH - SMALL_FONT_WIDTH,
      y + BIG_FONT_HEIGHT - 5);

  display.setFont(SMALL_FONT);

  printRight(
      "km/h",
      x + INFOBOX_WIDTH,
      y + INFOBOX_HEIGHT
  );
}