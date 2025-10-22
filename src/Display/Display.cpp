#include "Display.h"

void Display::printCenter(const char *text, uint8_t textX, uint8_t textY)
{
    unsigned int chars = strlen(text);
    unsigned char x = textX - ((chars * getMaxCharWidth()) / 2);

    drawStr(x, textY, text);
}

void Display::printCenter(int value, uint8_t textX, uint8_t textY)
{
    char buffer[DISPLAY_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%d", value);
    printCenter(buffer, textX, textY);
}

void Display::printCenter(float value, uint8_t textX, uint8_t textY)
{
    char buffer[DISPLAY_BUFFER_SIZE];
    dtostrf(value, 4, 2, buffer);
    printCenter(buffer, textX, textY);
}

void Display::printRight(const char *text, uint8_t textX, uint8_t textY)
{
    unsigned int chars = strlen(text);
    unsigned char x = textX - (chars * getMaxCharWidth());

    drawStr(x, textY, text);
}

void Display::printRight(int value, uint8_t textX, uint8_t textY)
{
    char buffer[DISPLAY_BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%d", value);
    printRight(buffer, textX, textY);
}

void Display::printRight(float value, uint8_t textX, uint8_t textY)
{
    char buffer[DISPLAY_BUFFER_SIZE];
    dtostrf(value, 4, 2, buffer);
    printRight(buffer, textX, textY);
}