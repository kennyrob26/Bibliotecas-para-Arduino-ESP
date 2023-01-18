/*
 * Exemplo de uso da biblioteca Ultrassonico
 * Biblioteca desenvolvida por Kenny
 * Data de criação: 18/01/2023
 * Ultima modificação: 
 */

#include <Ultrassonico.h>

#define TRIG 5
#define ECHO 6

//Definição das variáveis
float cm;
float pol;
float m;
float mm;

//dinstancia é uma instancia da classe Ultrassonico
Ultrassonico distancia(TRIG, ECHO); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  cm = distancia.emCentimetro();
  pol = distancia.emPolegada();
  m = distancia.emMetro();
  mm = distancia.emMilimetro();
  
  Serial.print("distância em centímetros: ");
  Serial.print(cm);
  Serial.println("cm");
  
  Serial.print("distância em Polegadas: ");
  Serial.print(pol);
  Serial.println("'");
  
  Serial.print("distância em metros: ");
  Serial.print(m);
  Serial.println("m");

  Serial.print("distância em milímetros: ");
  Serial.print(mm);
  Serial.println("mm");
  
  Serial.println("\n");
  
  delay(1500);
}
