#ifndef Ultrassonico_INCLUDED
#define Ultrassonico_INCLUDED

#include <Arduino.h>

class Ultrassonico{
    public:
        Ultrassonico(int trig, int echo);
        float pulso();
        float emCentimetro();
        float emPolegada();
        float emMetro();
        float emMilimetro();

    private:
        int trig;
        int echo;

};
















#endif