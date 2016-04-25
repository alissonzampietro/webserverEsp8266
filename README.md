#Trabalhando com requisições HTTP para o módulo Wi-Fi ESP-8266, enviando parâmetros 


## Descrição

Quando fui tentar implementar pela primeira vez o módulo ESP-8266 que poderia receber comandos para que fosse executado pelo meu arduíno, senti um pouco de dificuldade para encontrar documentação para isso, então criei esse algoritmo que acabou facilitando na hora de obter tais dados via URL.

## Passos

* Clone o projeto para a sua máquina
* O projeto já possui um HTML, se por acaso desejar customizar as cores dos círculos exibidos, atente-se em alterar as linhas 18,19,20 do arquivo index.html, o "id" corresponde a porta de saída do arduíno, e o círculo que corresponderá a cor do led no arduino, pode ser mudado o nome da cor que está escrita em 'class="circulo cor"', as cores disponíveis são: vermelho, branco, azul, amarelo, verde.
* O modelo do arduino é representado abaixo, está faltando somente as implementações dos jumpers, que deixei a disposição do desenvolvedor:

![Demo](https://raw.githubusercontent.com/alissonzampietro/webserver_esp8266_arduino/master/arduino.jpg)

* No arquivo do arduíno, não é necessário realizar nenhuma modificação. Para você saber o IP do seu ESP-8266, basta abrir o console após subir a aplicação para o seu arduíno.


## Como enviar dados para o arduíno:

Para enviar requisição para o arduíno, basta somente implementar a seguinte estrutura de código na URL: **http://IP_ESP8266_NA_SUA_REDE/?i=PORTAS_SAIDA_ARDUINO_SEM_ESPACO**.

Um exemplo da estrutura acima seria por exemplo:

`http://192.168.0.115/?i=76775676`

No código acima o valor **i** não é modificável, pois é por ele que o algoritmo no arquivo .ino identificará os comandos. Os números que são passados **76775676** cada um representa a porta do arduíno, não é necessário espaçamento e nada para separá-los.

*As portas disponíveis são de 4 a 9 temporariamente*