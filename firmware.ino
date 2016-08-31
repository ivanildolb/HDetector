#include "SIM900.h"
#include <SoftwareSerial.h>
#include "call.h"
 
CallGSM call;

//Constante que representa o pino onde o positivo 
//do buzzer será ligado.
const int buzzer = 8;
int pinopir = 4; //Pino ligado ao sensor PIR
int ledPin = 13; //Led no pino 13
int ldrPin = 0; //LDR no pino analógico 0
int ldrValor = 0; //Valor lido do LDR
int acionamento; //Valor do sensor de movimento
 
void setup()
{
     pinMode(pinopir, INPUT); //Define pino sensor como entrada     
     pinMode(buzzer,OUTPUT);
     pinMode(ledPin, OUTPUT); //Led indicador de movimento
     Serial.begin(9600);
     Serial.println("Testando GSM Shield...");     
     //Inicia a configuracao do Shield
     if (gsm.begin(2400))
          Serial.println("nstatus=READY");
     else Serial.println("nstatus=IDLE");
}
 
void loop()
{
  ///ler o valor do LDR
  ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
  Serial.print("Valor LDR: ");
  Serial.println(ldrValor);

  acionamento = digitalRead(pinopir); //Le o valor do sensor PIR  
  Serial.println(acionamento);
  if (acionamento == HIGH) // SE Movimento
  {    
    //se o valor lido for maior que 500, liga o led
    if (ldrValor>= 500) {
      digitalWrite(ledPin,HIGH);   
      delay(500);   
      digitalWrite(ledPin,LOW);    
    }

    Serial.println("movimento!!");
    //Ligando o buzzer com uma frequencia de 1500 hz.
    tone(buzzer,1500);   
    delay(500);
     
    //Desligando o buzzer.
    noTone(buzzer);
    delay(500);  
    
    /*Serial.println("Movimento");
    Serial.println("Discando....");
    //Efetua a chamada formato call.Call(<numero a ser chamado>)
    call.Call("04189994348161");
    
    for(int i = 0; i <= 14; i++){
      digitalWrite(13, HIGH);  
      delay(500);
      digitalWrite(13, LOW);
      delay(500);
    }
         
    Serial.println("Desligando...");
    call.HangUp();*/
  }

  //Serial.println("Parado");  
  delay(3000);  
  //do {} while (1); //Loop parando o programa
}
