#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include "../defines.h"

#ifdef WOKWI
    class Display : public U8G2_SSD1306_128X64_NONAME_1_HW_I2C {
        public:
            Display(
                const u8g2_cb_t *rotation
            ) : U8G2_SSD1306_128X64_NONAME_1_HW_I2C(
                    rotation
            ) {}
#endif

#ifdef SMARTVARIO
class Display : public U8G2_ST7565_JLX12864_1_4W_SW_SPI {
    public:
        Display(
            const u8g2_cb_t *rotation, 
            uint8_t clock, 
            uint8_t data, 
            uint8_t cs, 
            uint8_t dc, 
            uint8_t reset = U8X8_PIN_NONE
        ) : U8G2_ST7565_JLX12864_1_4W_SW_SPI(
                rotation, 
                clock,
                data,
                cs,
                dc,
                reset
        ) {}
#endif

    void printCenter(char *text, uint8_t textX, uint8_t textY);
    void printCenter(int value, uint8_t textX, uint8_t textY);
    void printCenter(float value, uint8_t textX, uint8_t textY);

    void printRight(char *text, uint8_t textX, uint8_t textY);
    void printRight(int value, uint8_t textX, uint8_t textY);
    void printRight(float value, uint8_t textX, uint8_t textY);
};

#endif