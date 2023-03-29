#include <U8g2lib.h>
#include "src/defines.h"
#include "src/helper/helper.h"
#include "src/Screen/Screen.h"

#ifndef DEMO
  #include "src/Variometer/Variometer.h"
  #include "src/Beep/Beep.h"
#endif

#ifdef WOKWI
U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0);
#endif

#ifdef SMARTVARIO
U8G2_ST7565_JLX12864_1_4W_SW_SPI display(
  U8G2_R0, 
  LCD_CLOCK_PIN,
  LCD_DATA_PIN,
  LCD_CS_PIN, 
  LCD_DC_PIN, 
  LCD_RESET_PIN
);
#endif

Screen screen;

#ifndef DEMO
  Variometer variometer;
  Beep beep(SPEAKER_PIN);
#endif

void setup(void) {
  startSound();

  delay(POWER_ON_DELAY);

  display.begin();
  display.setContrast(SCREEN_CONTRAST);
}

void loop(void) {
  #ifndef DEMO
    variometer.tick();
    beep.tick(variometer.getVario());

    screen.setDegree(0);
    screen.setAltitude(0);
    screen.setSpeed(0);
    screen.setVario(variometer.getVario());
  #endif

  screen.draw();
}

void startSound()
{
  tone(SPEAKER_PIN, 300, 500);
  delay(500);
  tone(SPEAKER_PIN, 400, 500);
  delay(500);
  tone(SPEAKER_PIN, 500, 500);
  delay(500);
}
