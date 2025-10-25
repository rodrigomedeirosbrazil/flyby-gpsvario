#define POWER_ON_DELAY 2000
#define SCREEN_CONTRAST 60
#define GPS_BAUD_RATE 9600
// TIMEZONE e TAKEOFF_SPEED agora são gerenciados pela classe Config

// Webserver configuration
#define WEBSERVER_WIFI_SSID "Flyby GPS Vario"
#define WEBSERVER_WIFI_PASSWORD ""
#define WEBSERVER_TIMEOUT 60000
#define WEBSERVER_WIFI_CHANNEL 6

#define SMALL_FONT u8g2_font_4x6_tr
#define SMALL_FONT_WIDTH 5
#define SMALL_FONT_HEIGHT 7

#define MEDIUM_FONT u8g2_font_5x8_tr
#define MEDIUM_FONT_WIDTH 5
#define MEDIUM_FONT_HEIGHT 8

#define BIG_FONT u8g2_font_t0_22_tr
#define BIG_FONT_WIDTH 10
#define BIG_FONT_HEIGHT 22

#define FLYBY_GPS_VARIO
// #define WOKWI

#ifdef FLYBY_GPS_VARIO
    #define SPEAKER_PIN 14
    #define LCD_DATA_PIN 21  // SDA
    #define LCD_CLOCK_PIN 22 // SCL
    #define GPS_TX_PIN 17
    #define GPS_RX_PIN 16
#endif

#ifdef WOKWI
    #define NO_BAROMETER
    #define NO_GPS
    #define SPEAKER_PIN 18
#endif