#ifndef WIND_H
#define WIND_H

class Wind
{
    public:
        Wind();
        void storeSpeed(unsigned long heading, float speed, unsigned long now);
        bool isAvailable();
        float getSpeed();
        unsigned long getDirection();
    private:
        unsigned long timeout;
        float speed;
        unsigned long direction;
        unsigned long lastCalculedWind;
        float speeds[16];
        unsigned long times[16];

        void calcWind(unsigned long now);
};

#endif