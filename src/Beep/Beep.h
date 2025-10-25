#ifndef BEEP_h
#define BEEP_h

class Beep {
  public:
    Beep(unsigned char pin);
    void tick(float vario);
    void setClimbRate(float climbRate);
    void setSinkRate(float sinkRate);

  private:
    float climbRate;  // Value will be loaded from Config
    float sinkRate;   // Value will be loaded from Config
    unsigned char pin;
    unsigned long beep;
    float    beepTime;
};

#endif




