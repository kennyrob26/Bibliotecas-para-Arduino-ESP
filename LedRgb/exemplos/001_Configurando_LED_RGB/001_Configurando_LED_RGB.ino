#include <LedRgb.h>

LedRgb ledRgb(2, 4, 16);
void setup() {

  
}

void loop() {
  // put your main code here, to run repeatedly:
  //vermelho
  ledRgb.cor(255, 0, 0);
  delay(1000);
  //laranja
  
  ledRgb.cor(255, 165, 0);
  delay(1000);
  //amarelo
  ledRgb.cor(255, 255, 0);
  delay(1000);
  //verde
  ledRgb.cor(0, 255, 0);
  delay(1000);
  //azul
  ledRgb.cor(0, 0, 255);
  delay(1000);
  //roxo
  ledRgb.cor(186,85,211);
  delay(1000);
}
