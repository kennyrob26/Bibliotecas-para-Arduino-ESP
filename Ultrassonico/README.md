# Biblioteca Ultrassonico para sensor HC-SR04

A biblioteca retorna a distância utilizando o sensor ultrassônico HC-SR04  
Os valores utilizados para a medição da distância está presente no datasheet: https://datasheetspdf.com/pdf-file/1380137/HandsOn/HC-SR04/1  
Lembrando que a distância que o sensor opera está entre 2cm e 400cm, ou seja, em distância maiores que 4 metros a possibilidade de receber dados incorretos é muito grande. Por isso a biblioteca verifica se o puso foi maior que 23200, em caso afirmativo retorna NULL  
Para mais detalhes sobre o sensor acesse o datasheet do componente, vamos conhecer agora os métodos presentes na biblioteca  
## Métodos

**`Ultrassonico(int trig, int echo)`** -> é o método construtor, onde:  
	**`int trig`** -> é a porta onde está conectado o pino trigger  
	**`int echo`** -> é a porta onde está conectado o pino echo  

**`pulso()`** -> Retorna o tempo do pulso que o echo recebeu, possibilitando assim que o usuário use esse dado da maneira que desejar  

**`emCentimetro()`** -> Retorna a distância em centimetro  

**`emPelegada()`** -> retona a distância em polegadas  

**`emMetro()`** -> Converte o resultado de 'emCentimetro()' para metros  

**`emMilimetro()`** -> Converte o resultado de 'emCentimetro' para milímetros  

## Como utilizar 

A utilização é muito simples e pode ser vista no arquivo exemplo.ino, mas de forma resumida o funcionamento, apenas criamos uma instância da classe **`Ultrassonico`** e definimos os pinos trigger e echo, e após isso podemos utilizar qualquer um dos métodos que vimos a cima

