const byte LONGE=100;
const byte PERTO=50;
const byte UM=0;
const byte DOIS=1;
const byte TRES=2;
const byte pinLed=6;

//Declaração das variáveis referentes aos pinos digitais.
byte PIR[]  = {12,11,10};
byte PROX[] = {150, 100, 75};

byte pinBuzzer = 7;
byte pinRele   = 3;

byte armaRele[]= {0,0,0};
byte valorPIR[] = {0,0,0};

int tempo = 0;
byte mudanca = 0;
byte resetaRele = LOW;


void setup() {
  Serial.begin(14400); //Inicializando o serial monitor
  //Definido pinos como de entrada ou de saída
  
  pinMode(pinBuzzer,OUTPUT);
  pinMode(pinRele,  OUTPUT);
  pinMode(pinLed,   OUTPUT);
  for(int i=UM; i<=TRES; i++){
    pinMode(PIR[i],INPUT);
  }
  digitalWrite(pinRele, LOW);
  Serial.println("PIR Um: PIR Dois: PIR Tres: Tempo:");  
}
 
void loop() {  
  //Lendo o valor do sensor PIR. Este sensor pode assumir 2 valores
  //1 quando detecta algum movimento e 0 quando não detecta.
  
  
  for(int i=UM; i<=TRES; i++){
    valorPIR[i] = digitalRead(PIR[i]);
    Serial.print(valorPIR[i]);
    Serial.print(":");
  }
  Serial.print((int)tempo/4);
  Serial.println(":");
  
  //Verificando se ocorreu detecção de movimentos



  for(int i=UM; i<=TRES; i++){
    if(valorPIR[i]==HIGH){
      ligarAlarme(i);
    }else{
      desligarAlarme();
      delay(200);
    }
  }
  
  tempo++;
  delay(50);
}
 
void ligarAlarme(byte Qual) {
  int i;
  armaRele[Qual]=HIGH;
  switch(Qual){
    case UM:
      digitalWrite(pinLed, HIGH);
      for(i=0;i<Qual+1;i++){
        tone(pinBuzzer,1450);
        delay(PROX[i]);
        noTone(pinBuzzer);
        delay(PROX[i]);
      }
      digitalWrite(pinLed, LOW);
      break;
    case DOIS:
      digitalWrite(pinLed, HIGH);
      for(i=0;i<Qual+1;i++){
        tone(pinBuzzer,1380);
        delay(PROX[i]);
        noTone(pinBuzzer);
        delay(PROX[i]);
      }
      digitalWrite(pinLed, LOW);
      break;
    case TRES:
      digitalWrite(pinLed, HIGH);
      digitalWrite(pinRele, HIGH);
      for(i=0;i<Qual+1;i++){
        tone(pinBuzzer,1630);
        delay(PROX[i]);
        noTone(pinBuzzer);
        delay(PROX[i]);
      }
      digitalWrite(pinLed, LOW);
      break;
  }
  //Ligando o led
//  digitalWrite(pinLed, HIGH);

//  delay(500); //tempo que o led fica acesso e o buzzer toca
//  desligarAlarme();
  if(armaRele[UM]==HIGH&&armaRele[DOIS]==HIGH&&armaRele[TRES]==HIGH){
    digitalWrite(pinRele, HIGH);
  }else if(resetaRele == 1){
    armaRele[UM]=LOW;
    armaRele[DOIS]=LOW;
    armaRele[TRES]=LOW;
    resetaRele = LOW;
    digitalWrite(pinRele, LOW);
  }
}
 
void desligarAlarme() {
  //Desligando o led
  digitalWrite(pinLed, LOW);
  //Desligando o buzzer
//  noTone(pinBuzzer);
}

