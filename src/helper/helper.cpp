#include <U8g2lib.h>
#include "helper.h"

void printHorizontalCenter(const char *text, uint8_t textX, uint8_t textY)
{
    unsigned int chars = strlen(text);
    unsigned char x = chars * display.getMaxCharWidth();

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

uint8_t countDigits(int num)
{
    return (1 + log10(num));
}