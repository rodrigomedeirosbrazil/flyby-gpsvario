#define POWER_ON_DELAY 2000
#define SCREEN_CONTRAST 60
#define GPS_SERIAL_BAUD_RATE 9600
#define TIMEZONE -3

#define INFOBOX_WIDTH 64
#define INFOBOX_HEIGHT 20

#define SMALL_FONT u8g_font_5x7
#define SMALL_FONT_WIDTH 5
#define SMALL_FONT_HEIGHT 7

#define BIG_FONT u8g2_font_10x20_tr
#define BIG_FONT_WIDTH 10
#define BIG_FONT_HEIGHT 20

// #define SMARTVARIO

#ifdef SMARTVARIO
    #define SPEAKER_PIN 9
    #define LCD_CS_PIN 6
    #define LCD_RESET_PIN 5
    #define LCD_DC_PIN 4 // RS
    #define LCD_DATA_PIN 3  // SDA
    #define LCD_CLOCK_PIN 2 // SCL
#endif

#define WOKWI

#ifdef WOKWI
    #define SPEAKER_PIN 13
#endif