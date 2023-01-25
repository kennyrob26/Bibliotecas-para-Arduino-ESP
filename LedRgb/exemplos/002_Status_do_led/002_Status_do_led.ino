#include <LedRgb.h>

LedRgb ledRgb(2, 4, 16);
void setup() {
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //vermelho
  ledRgb.cor(255, 0, 0);
  //int valorR = ledRgb.getLedR();
  //Serial.println(valorR);
  delay(1000);
  
  //verde
  ledRgb.cor(0, 255, 0);
  //int valorG = ledRgb.getLedG();
  //Serial.println(valorG);
  delay(1000);
  

  //azul
  ledRgb.cor(0, 0, 255);
  //int valorB = ledRgb.getLedB();
  //Serial.println(valorB);
  delay(1000);

}
