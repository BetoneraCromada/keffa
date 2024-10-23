/*
==============================================================================

  /$$$$$$  /$$           /$$                                              
 /$$__  $$| $$          | $$                                              
| $$  \ $$| $$  /$$$$$$ | $$$$$$$   /$$$$$$  /$$$$$$$   /$$$$$$  /$$   /$$
| $$$$$$$$| $$ /$$_  $$| $$_  $$ |__  $$| $$_  $$ /$$_  $$|  $$ /$$/
| $$__  $$| $$| $$  \ $$| $$  \ $$  /$$$$$$$| $$  \ $$| $$  \ $$ \  $$$$/ 
| $$  | $$| $$| $$  | $$| $$  | $$ /$$__  $$| $$  | $$| $$  | $$  >$$  $$ 
| $$  | $$| $$| $$$$$$$/| $$  | $$|  $$$$$$$| $$  | $$|  $$$$$$/ /$$/\  $$
|/  |/|/| $$/ |/  |/ \/|/  |/ \/ |/  \_/
              | $$                                                        
              | $$                                                        
              |/                                                        
                                 ___
                          .--""'-----,   "--..
                       .-''   /      ; .'"----,-,
                     .'      :_:     ; :      ;;..
                    .      _.- _.-    .' :      ::  ..
                 _;..----------------' :: __  ::   ;;
            .--"". '           .....:=()-' :--'.
          .'   .'         .--''__       :       ==:    ;
      .--/    /        .'.''     -,   :         :   '-.
   ."', :    /       .'-\\       .--.\ :         :  ,   _\
  ;   ; |   ;       /:'  ;;      /_  \\:         :  :  /\\
  |\/  |   |      / \_//      /"--\\ \:         :  : ;|\|    
  : "  /\/\//   """      /     \\ :         :  : :|'||
["""""""""--------........._  /      || ;      __.:--' :|//|
 "------....__         ].'|      // |--"""'...-'\ \//
   | WVE230L |;...--'": :  \    //  |---"""      \\/
     """""""""'            \ \  \_.//  /
       ---'                \ \_     _'
                             -----'  
===============================================================================

by Alphanox² v1.0.1 COPYRIGHT © todos os direitos reservados.

Ana B.
Caio V.
Gabriel R.
Julia R.

=================================================================================
*/

#define pontoDeCorteDoSensor 500
#define pinoRele 5

unsigned long int tempos[5] = {};
const int pinos[] = {A0, A1, A2, A3};
bool estadoRele = false;

// Declaração das funções
void mostrarTodosOsTempos();
void resetar();
void mostrarTodosOsValores();
void registrarTempo(int i);
void terminou();

void setup() {
  Serial.begin(9600);
  // Definindo os pinos como entrada
  int tamanhoPinos = sizeof(pinos) / sizeof(pinos[0]);
  for (int i = 0; i < tamanhoPinos; i++) {
    pinMode(pinos[i], INPUT);
  }
  pinMode(pinoRele, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    char caractere = Serial.read();
    switch (caractere) {
      case 'a':
        mostrarTodosOsTempos();
        break;
      case 'r':
        resetar();
      break;
      case 'd':
        mostrarTodosOsValores();
      break;
      case 's':
        estadoRele = false;
        Serial.println("Começando em...");
        delay(100);
        Serial.println("3...");
        delay(500);
        Serial.println("2..");
        delay(500);
        Serial.println("1");
        delay(500);
        Serial.println("Experimento iniciado! HEHEHEHE");
        estadoRele = true;
        tempos[0] = millis();
      break;
    }
  }

  if(estadoRele){
    digitalWrite(pinoRele, HIGH);
    int tamanhoPinos = sizeof(pinos) / sizeof(pinos[0]);
    for (int i = 0; i < tamanhoPinos; i++) {
      int valorLidoDoSensor = analogRead(pinos[i]);
      if(valorLidoDoSensor > pontoDeCorteDoSensor){
        registrarTempo(i);
      }
    }
  }else{
    digitalWrite(pinoRele, LOW);
  }
}
void mostrarTodosOsValores(){
  for (int i = 0; i <= 4; i++) {
    int valorLidoDoSensor = analogRead(pinos[i]);
    Serial.print("Sensor: "+(String)i);
    Serial.println(" -> "+(String)valorLidoDoSensor);
  }
}

void mostrarTodosOsTempos(){
  for (int i = 0; i <= 4; i++) {
    Serial.println(tempos[i]);
  }
}

void resetar(){
  estadoRele = false;
  for (int i = 0; i <= 4; i++) {
    tempos[i] = 0;
  }
  Serial.println("Experimento resetado!");
}

void registrarTempo(int i){
  if(tempos[i-1] != 0 && tempos[i] == 0 && i != 0){
    Serial.println("O sensor"+(String)i+"acabou de medir!");
    tempos[i+1] = millis() - tempos[0];
    if(i == 3){
      terminou();
    }
  }
}

void terminou() {
  estadoRele = false;
  mostrarTodosOsTempos();
  resetar();
  Serial.println("Experimento finalizado!");
}
