#ifndef BEEP_h
#define BEEP_h

class Beep {
  public:
    Beep(unsigned char pin);
    void tick(float vario);
    void setClimbRate(float climbRate);
    void setSinkRate(float sinkRate);

  private:
    float climbRate = 0.1;
    float sinkRate = -2.0;
    unsigned char pin;
    unsigned long beep;
    float    beepTime;
};

#endif




