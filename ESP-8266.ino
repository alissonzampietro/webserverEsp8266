#include <SoftwareSerial.h>
 
//RX pino 2, TX pino 3
SoftwareSerial esp8266(2, 3);
 
#define DEBUG true 
void setup()
{
  Serial.begin(9600);
  esp8266.begin(115200);

  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
 
  sendData("AT+RST\r\n", 2000, DEBUG); // rst
  // Conecta a rede wireless
  sendData("AT+CWJAP=\"NOME_REDE\",\"SENHA\"\r\n", 2000, DEBUG);
  delay(3000);
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG);
  // Mostra o endereco IP
  sendData("AT+CIFSR\r\n", 1000, DEBUG);
  // Configura para multiplas conexoes
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG);
  // Inicia o web server na porta 80
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG);
}
 
void loop()
{
  // Verifica se o ESP8266 esta enviando dados
  if (esp8266.available())
  {
    if (esp8266.find("+IPD,"))
    {
      delay(300);
      int connectionId = esp8266.read() - 48;
 
      String webpage = "<head>";
      webpage += "</head><h1><u>ESP8266 - Web Server</u></h1>";
 
      String cipSend = "AT+CIPSEND=";
      cipSend += connectionId;
      cipSend += ",";
      cipSend += webpage.length();
      cipSend += "\r\n";
 
      sendData(cipSend, 1000, DEBUG);
      sendData(webpage, 1000, DEBUG);
 
      String closeCommand = "AT+CIPCLOSE=";
      closeCommand += connectionId; // append connection id
      closeCommand += "\r\n";
 
      sendData(closeCommand, 3000, DEBUG);
    }
  }
}

void ascenderLuz(String comando){
  if(comando != "&" && comando != "=" && comando != ""){
    int cmd = comando.toInt();
    digitalWrite(cmd,HIGH);
    delay(1000);
    digitalWrite(cmd,LOW);
    delay(1000);
  }
}
 
String sendData(String command, const int timeout, boolean debug)
{
  // Envio dos comandos AT para o modulo
  String response = "";
  String caracter = "";
  esp8266.print(command);
  long int time = millis();
  int ativo = 0;
  int igual = 0;
  int cont = 3;
  while ( (time + timeout) > millis())
  {
    while (esp8266.available())
    {
      // The esp has data so display its output to the serial window
      char c = esp8266.read(); // read the next character.
      caracter = c;
      if(caracter == "?" || ativo == 1){
        cont--;
        ativo = 1;
        if(cont <= 0){
          if(caracter == "H"){
            ativo = 0;
          }else{
            ativo = 1;
            ascenderLuz(caracter);
          }
        }
      }
      response += c;
    }
  }
  if (debug)
  {
    //exibirá todas as informações no console
    Serial.print(response);
  }
  return response;
}
