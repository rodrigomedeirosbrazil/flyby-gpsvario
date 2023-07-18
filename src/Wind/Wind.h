#ifndef WIND_H
#define WIND_H

class Wind
{
    public:
        void storeSpeed(unsigned long heading, float speed, unsigned long now);
        bool isAvailable();
        float getSpeed();
        unsigned long getDirection();
    private:
        const unsigned long timeout = 10000;
        float speed = 0;
        unsigned long direction = 0;
        unsigned long lastCalculedWind = 0;
        float speeds[16];
        unsigned long times[16];

        void calcWind(unsigned long now);
};

#endif