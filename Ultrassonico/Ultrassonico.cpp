#include <Ultrassonico.h>

//Definição dos pinos 
Ultrassonico::Ultrassonico(int trig, int echo){
    this->trig = trig;
    this->echo = echo;

    //define trig como saida e echo como entrada
    pinMode(this->trig, OUTPUT);
    pinMode(this->echo, INPUT);

    
}
// Caso o usuário desejar tratar o pulso em  outra medida,
// pulso() retorna apenas apenas o tamanho do pulso
float Ultrassonico::pulso(){
    pinMode(trig, HIGH);
    delayMicroseconds(10);
    pinMode(trig, LOW);
    float pulse =  pulseIn(echo, HIGH);

    //o valor 23200 representa 400 cm, que é o valor maximo do sensor
    if (pulse <= 23200){
        return pulse;
    } else{
        return NULL;
    }
    
}
 
//Retorna a distância em centimetros, pulso/58 é a fórmula indicada no datasheet do componente
float Ultrassonico::emCentimetro(){
    float pulse = pulso();
    float cm = (pulse/58);
    return cm;
}
//retorna a distância em polegadas
float Ultrassonico::emPolegada(){
    float pulse = pulso();
    float pol = (pulse/ 148);
    return pol;
}
//retorna a distância em metros
float Ultrassonico::emMetro(){
    float cm = emCentimetro();
    float m = (cm/100);
    return m;
}
//Retorna a distância em mm
float Ultrassonico::emMilimetro(){
    float cm = emCentimetro();
    float mm = (cm *10);
    return mm;
}