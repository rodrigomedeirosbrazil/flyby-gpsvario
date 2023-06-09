#define POWER_ON_DELAY 2000
#define SCREEN_CONTRAST 60
#define GPS_BAUD_RATE 9600
#define TIMEZONE -3
#define TAKEOFF_SPEED 6

#define SMALL_FONT u8g_font_5x7
#define SMALL_FONT_WIDTH 5
#define SMALL_FONT_HEIGHT 7

#define BIG_FONT u8g2_font_10x20_tr
#define BIG_FONT_WIDTH 10
#define BIG_FONT_HEIGHT 20

#define FLYBY_GPS_VARIO
// #define WOKWI
// #define SMARTVARIO

#ifdef FLYBY_GPS_VARIO
    #define SPEAKER_PIN 14
    #define LCD_DATA_PIN 21  // SDA
    #define LCD_CLOCK_PIN 22 // SCL
    #define GPS_TX_PIN 17
    #define GPS_RX_PIN 16
#endif

#ifdef SMARTVARIO
    #define SPEAKER_PIN 9
    #define LCD_CS_PIN 6
    #define LCD_RESET_PIN 5
    #define LCD_DC_PIN 4 // RS
    #define LCD_DATA_PIN 3  // SDA
    #define LCD_CLOCK_PIN 2 // SCL
#endif

#ifdef WOKWI
    #define NO_BAROMETER
    #define NO_GPS
    #define SPEAKER_PIN 18
#endif