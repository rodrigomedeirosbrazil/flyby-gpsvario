#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(U8G2_R0);

#define pi 3.141593

unsigned int degree = 0;
unsigned int altitude = 100;
unsigned int speed = 45;

unsigned char compassX=25;
unsigned char compassY=25;
unsigned char compassSize=25;

void setup(void) {
  display.begin();
}

void loop(void) {
  display.firstPage();
  do {
    drawCompass();
    drawAltitude();
  } while (display.nextPage());
  delay(100);
  degree = degree >= 360 
    ? 0
    : degree + 5;
  
  altitude = altitude > 2000
    ? 0
    : altitude + 20;

  speed = speed > 60
    ? 0
    : speed + 5;
}

void drawCompass() {
  display.setFont(u8g_font_5x7);
  drawCompassCircles();
  drawNorth();
  drawSouth();
  drawEast();
  drawWest();
  drawCompassDegree();
}

void drawCompassCircles() {
  display.drawCircle(compassX, compassY, compassSize);
  display.drawCircle(compassX, compassY, compassSize-10);
}

void drawNorth() {
  unsigned int compassDegree = 360 - degree;
  unsigned char x = ((cos((compassDegree+270) * (pi / 180))) * (compassSize - 5) )+compassX;
  unsigned char y = ((sin((compassDegree+270) * (pi / 180))) * (compassSize - 5))+compassY+6;
  
  display.setCursor(x-(display.getMaxCharWidth()/2), y-(display.getMaxCharHeight()/2));
  display.print("N");
}

void drawSouth() {
  unsigned int compassDegree = 360 - degree;
  unsigned char x = ((cos((compassDegree+90) * (pi / 180))) * (compassSize - 5))+compassX;
  unsigned char y = ((sin((compassDegree+90) * (pi / 180))) * (compassSize - 5))+compassY+6;
  
  display.setCursor(x-(display.getMaxCharWidth()/2), y-(display.getMaxCharHeight()/2));
  display.print("S");
}

void drawEast() {
  unsigned int compassDegree = 360 - degree;
  unsigned char x = ((cos(compassDegree * (pi / 180))) * (compassSize - 5))+compassX;
  unsigned char y = ((sin(compassDegree * (pi / 180))) * (compassSize - 5))+compassY+6;
  
  display.setCursor(x-(display.getMaxCharWidth()/2), y-(display.getMaxCharHeight()/2));
  display.print("E");
}

void drawWest() {
  unsigned int compassDegree = 360 - degree;
  unsigned char x = ((cos((compassDegree+180) * (pi / 180))) * (compassSize - 5))+compassX;
  unsigned char y = ((sin((compassDegree+180) * (pi / 180))) * (compassSize - 5))+compassY+6;
  
  display.setCursor(x-(display.getMaxCharWidth()/2), y-(display.getMaxCharHeight()/2));
  display.print("W");
}

void drawCompassDegree() {
  printNumberCenter(
    degree, 
    compassX, 
    compassY + compassSize + display.getMaxCharHeight() + 1
  );
}

void drawAltitude() {
  display.setFont(u8g2_font_courB24_tn);
  display.setCursor(64, display.getMaxCharHeight());
  display.print(altitude);
}

void printHorizontalCenter(const char* text, uint8_t textX, uint8_t textY) {
  unsigned int chars = strlen(text);
  unsigned char x = chars * display.getMaxCharWidth();

  display.setCursor(x, textY);
  display.print(text);
}

void printNumberCenter(int num, uint8_t textX, uint8_t textY) {
  unsigned int chars = countDigits(num);
  unsigned char x = textX - ((chars * display.getMaxCharWidth())/2);

  display.setCursor(x, textY);
  display.print(num);
}

uint8_t countDigits(int num)
{
   return(1 + log10(num));
}