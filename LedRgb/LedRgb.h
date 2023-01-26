/*
 *Bibioteca desenvolvida por Kenny Robert
 *Desenvolvida em 25/01/2023
 *Ultima modificação em: 26/01/2023
 *
 * O objetivo da biblioteca é facilitar o uso de leds RGB no ESP32
 * O usuário apenas instancia um objeto da classe LedRgb, e define os pinos para cada cor
 * Depois disso é só utilizar a função cor, colocando em sequência os valores para R, G e B
 */

#ifndef LedRgb_INCLUDED
#define LedRgb_INCLUDED

#include <Arduino.h>

class LedRgb{
    public: 
        LedRgb(int pinoR, int pinoG, int pinoB);
        void setCanais(int canalR, int canalG, int canalB);
        void setFrequencia(int freq);
        void setCiclo(int c);
        void cor(int red, int green, int blue);
        void corR(int red);
        void corG(int green);
        void corB(int blue);
        int getCorR();
        int getCorG();
        int getCorB();

    private:
        //GPIOs
        int ledR;   //pino led vermelho
        int ledG;   //pino led verde
        int ledB;   //pino led azul

        //Armazenam a cor atual
        int red;
        int green;
        int blue;

        //Configurações do pwm
        int frequencia;
        int ciclo; 
        int canalR;
        int canalG;
        int canalB;

};


#endif