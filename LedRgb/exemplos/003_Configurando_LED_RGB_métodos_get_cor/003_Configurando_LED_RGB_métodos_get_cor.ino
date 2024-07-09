#include <LedRgb.h>

/*
 *Exemplo simples utilizando apenas a cor vermelha,
 * onde o método get retorna o ultimo valor setado para a cor vermelha
 *resumindo, retorna o "estado atual" do led
 */

LedRgb ledRgb(2, 4, 16);
void setup() {
  Serial.begin(115200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<=255; i++){
    ledRgb.corR(i);
    Serial.println(ledRgb.getCorR());
    delay(5);
  }
  for(int i=255; i>=0; i--){
    ledRgb.corR(i);
    Serial.println(ledRgb.getCorR());
    delay(5);
  }


}
