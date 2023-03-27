
#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_1_HW_I2C display;
extern unsigned int degree;
extern unsigned char compassX;
extern unsigned char compassY;
extern unsigned char compassSize;

void drawCompass();
void drawCompassCircles();
void drawNorth();
void drawSouth();
void drawEast();
void drawWest();
void drawCompassDegree();


