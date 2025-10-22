#ifndef DISPLAY_H
#define DISPLAY_H

#include <U8g2lib.h>
#include "../defines.h"

// Buffer size for text formatting functions
#define DISPLAY_BUFFER_SIZE 16

#ifdef FLYBY_GPS_VARIO
    class Display : public U8G2_ST7567_ENH_DG128064I_F_HW_I2C {
        public:
            Display(
                const u8g2_cb_t *rotation,
                uint8_t reset,
                uint8_t clock,
                uint8_t data = U8X8_PIN_NONE
            ) : U8G2_ST7567_ENH_DG128064I_F_HW_I2C(
                    rotation, reset, clock, data
            ) {}
#endif

#ifdef WOKWI
    class Display : public U8G2_SSD1306_128X64_NONAME_1_HW_I2C {
        public:
            Display(
                const u8g2_cb_t *rotation
            ) : U8G2_SSD1306_128X64_NONAME_1_HW_I2C(
                    rotation
            ) {}
#endif

    void printCenter(const char *text, uint8_t textX, uint8_t textY);
    void printCenter(int value, uint8_t textX, uint8_t textY);
    void printCenter(float value, uint8_t textX, uint8_t textY);

    void printRight(const char *text, uint8_t textX, uint8_t textY);
    void printRight(int value, uint8_t textX, uint8_t textY);
    void printRight(float value, uint8_t textX, uint8_t textY);
};

#endif