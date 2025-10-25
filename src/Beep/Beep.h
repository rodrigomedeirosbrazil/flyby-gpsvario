#ifndef BEEP_h
#define BEEP_h

class Beep {
  public:
    Beep(unsigned char pin);
    void tick(float vario);
    void setClimbRate(float climbRate);
    void setSinkRate(float sinkRate);

  private:
    float climbRate;  // Valor será carregado da Config
    float sinkRate;   // Valor será carregado da Config
    unsigned char pin;
    unsigned long beep;
    float    beepTime;
};

#endif




