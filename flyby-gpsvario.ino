#include <U8g2lib.h>
#include "src/defines.h"
#include "src/helper/helper.h"
#include "src/Screen/Screen.h"
// #include "src/Variometer/Variometer.h"
// #include "src/Beep/Beep.h"

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0);

Screen screen;
// Variometer variometer;
// Beep beep(SPEAKER_PIN);

void setup(void) {
  display.begin();
}

void loop(void) {
  // variometer.tick();
  // beep.tick(variometer.getVario());

  // screen.setDegree(degree);
  // screen.setAltitude(altitude);
  // screen.setSpeed(speed);
  // screen.setVario(vario);
  screen.draw();

}
