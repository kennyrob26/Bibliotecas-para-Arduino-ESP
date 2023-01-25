#include <LedRgb.h>

//Definição dos pinos do led RGB

LedRgb::LedRgb(int pinoR, int pinoG, int pinoB){
    //Definições básica
    this->ledR = pinoR;
    this->ledG = pinoG;
    this->ledB = pinoB;

    //por padrão:
    setCanais(0, 1, 2);
    setFrequencia(5000);
    setCiclo(8);

    //definindo os pinos como OUTPUT
    pinMode(ledR, OUTPUT);
    pinMode(ledG, OUTPUT);
    pinMode(ledB, OUTPUT);

    //Configurações do pwm
    ledcSetup(canalR, frequencia, ciclo);
    ledcSetup(canalG, frequencia, ciclo);
    ledcSetup(canalB, frequencia, ciclo);

    //Atribuindo leds aos seus respectivos canais
    ledcAttachPin(ledR, canalR);
    ledcAttachPin(ledG, canalG);
    ledcAttachPin(ledB, canalB);

}

void LedRgb::setCanais(int canalR, int canalG, int canalB){
    this->canalR = canalR;
    this->canalG = canalG;
    this->canalB = canalB;
}

void LedRgb::setFrequencia(int freq){
    this->frequencia = freq;
}

void LedRgb::setCiclo(int c){
    this->ciclo = c;
}

void LedRgb::cor(int red, int green, int blue){
    ledcWrite(canalR, red);
    ledcWrite(canalG, green);
    ledcWrite(canalB, blue);
}

