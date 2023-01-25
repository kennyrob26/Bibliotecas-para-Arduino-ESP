# Biblioteca LedRgb

## Obejetivos
A biblioteca LedRgb tem como finalidade facilitar o uso de leds RGB, com poucas linhas de códico o usuário já consegue setar cores seguindo o padrão RGB  
Encontramos um simples exemplo de uso dentro da pasta exemplo desse repositório  

## Como utilizar
Logo após incluirmos a bilbioteca **ledRgb.h**, devemos instanciar o objeto da classe LedRgb, o método construtor recebe como parâmetro os pinos R, G e B, em sequência  
`LedRgB ledRgb(pinoRed, pinoGreen, pinoBlue).`  
**Exemplo de uso**
`LedRgb ledRgb(2, 4, 16);` Ou seja, A GPIO 2 é o pino equivalente ao vermelho, 4 equivale ao verde e 16 ao azul  
Não é necessário nenhuma configuração no **setup**  
Partindo diretamente para o **loop**, nós chamamos o método cor, que recebe como parâmetro o valor de R, G e B.  
`ledRgb.cor(valorRed, valorGreen, ValorBlue);`  
**Exemplo de uso**  
`ledRgb.cor(255, 0, 0);` O led ficará na cor vermelha  
`ledRgb.cor(0, 255, 0);` O led ficaŕa na cor verde  
`ledRgb.cor(0, 0, 255);` O led ficará na cor azul  

## Como mudar as predefinições
Por padrão a biblioteca já vem com as configurações pwm pré definidas, como o canal, a frequência e o cliclo (resolução) do pwm;

**canal:** por padrão a biblioteca utiliza respectivamente os **canais 0, 1 e 2**, para as cores vermelho, verde e azul. Caso o usuário tenha a necessidade de alterar os canais é só utilizar o método setCanais(), que recebe um inteiro de **0 à 15**  
`setCanais(canalVermelho, canalVerde, canalAzul);`  

**frequência:** por padrão a biblioteca utiliza o **valor 5000**, para alterar esse valor utilizamos o método setFrequencia(), que recebe um inteiro de  **1 à 40.000.000**  
`setFrequencia(valorDesejado);`  

**ciclo:** o ciclo ou também chamado de **resolução**, por padrão é definido como **8 bits**, o valor pode ser alterado utilizando o método setCiclo(), que recebe um inteiro de no **máximo 16 bits**  
`setCiclo(valorDesejado);`




