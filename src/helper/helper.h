#include <U8g2lib.h>

extern U8G2_SSD1306_128X64_NONAME_1_HW_I2C display;

void printCenter(const char *text, uint8_t textX, uint8_t textY);
void printRight(const char *text, uint8_t textX, uint8_t textY);
void printNumberCenter(int num, uint8_t textX, uint8_t textY);
void printNumberRight(int num, uint8_t textX, uint8_t textY);
uint8_t countDigits(int num);
void drawInfoBox(int num, const char *unit, uint8_t x, uint8_t y);
