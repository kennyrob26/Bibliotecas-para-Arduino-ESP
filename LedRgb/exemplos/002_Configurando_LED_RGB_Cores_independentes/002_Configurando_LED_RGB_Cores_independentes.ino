#include <LedRgb.h>

LedRgb ledRgb(2, 4, 16);
void setup() {

  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Altera apenas o vermelho
  ledRgb.cor(0,0,0);
  ledRgb.corR(255);
  delay(1000);

  //Altera verde e vermelho
  ledRgb.cor(0,0,0);
  ledRgb.corR(255);
  ledRgb.corG(255);
  delay(1000);

  //Altera apenas o verde
  ledRgb.cor(0, 0, 0);
  ledRgb.corG(255);
  delay (1000);

  //Altera verde e azul
  ledRgb.cor(0,0,0);
  ledRgb.corG(255);
  ledRgb.corB(255);
  delay(1000);


  //Altera apenas o azul
  ledRgb.cor(0,0,0);
  ledRgb.corB(255);
  delay(1000);

}
