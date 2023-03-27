#include <U8g2lib.h>
#include "helper.h"
#include "../defines.h"

void printCenter(const char *text, uint8_t textX, uint8_t textY)
{
    unsigned int chars = strlen(text);
    unsigned char x = textX - ((chars * display.getMaxCharWidth()) / 2);

    display.setCursor(x, textY);
    display.print(text);
}

void printRight(const char *text, uint8_t textX, uint8_t textY)
{
    unsigned int chars = strlen(text);
    unsigned char x = textX - (chars * display.getMaxCharWidth());

    display.setCursor(x, textY);
    display.print(text);
}

void printNumberCenter(int num, uint8_t textX, uint8_t textY)
{
    unsigned int chars = countDigits(num);
    unsigned char x = textX - ((chars * display.getMaxCharWidth()) / 2);

    display.setCursor(x, textY);
    display.print(num);
}

void printNumberRight(int num, uint8_t textX, uint8_t textY)
{
    unsigned int chars = countDigits(num);
    unsigned char x = textX - (chars * (display.getMaxCharWidth() + 1));

    display.setCursor(x, textY);
    display.print(num);
}

uint8_t countDigits(int num)
{
    return num < 0 
        ? (1 + log10(abs(num))) + 1
        : num == 0 ? 1 : (1 + log10(num));
}

void drawInfoBox (int num, const char* unit, uint8_t x, uint8_t y)
{
    // display.drawFrame(x, y, INFOBOX_WIDTH, INFOBOX_HEIGHT);

    display.setFont(BIG_FONT);

    printNumberRight(
        num,
        x + INFOBOX_WIDTH - SMALL_FONT_WIDTH,
        y + BIG_FONT_HEIGHT - 5);

    display.setFont(SMALL_FONT);

    printRight(
        unit,
        x + INFOBOX_WIDTH,
        y + INFOBOX_HEIGHT);
}