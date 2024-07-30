#include <SoftwareSerial.h> //para utilização do módulo bluetooth

const int pinoLDR1 = A2;
const int pinoLDR2 = A3;
const int pinoRX = 11;
const int pinoTX = 10;

//O threshold é usado para monitorar o sensor LDR, quando o sensor retornar acima do threshold consideramos que a bolinha passou por ele
//O LDR retorna 1 quando estiver recebendo o máximo de luz e 1000 quando não estiver recebendo luz
//O threshold precisa ser calibrado através do bluetooth de acordo com o ambiente
int thresholdDoLDR = 300;

bool debugMode = false;

SoftwareSerial bluetooth(pinoRX, pinoTX);

unsigned long tempoQueABolinhaPassouNoLDR1 = 0;
unsigned long tempoQueABolinhaPassouNoLDR2 = 0;

void imprime(char* mensagem) {
  Serial.print(mensagem);
  bluetooth.print(mensagem);
}

void setup(){
  Serial.begin(115200);
  bluetooth.begin(9600);

  pinMode(pinoLDR1, INPUT);
  pinMode(pinoLDR2, INPUT);

  imprime("Envie 1 para habilitar debug e 0 para desabilitar\n");
  imprime("Para mudar o threshold envie 2 para 200, 3 para 300 e assim por diante até 9\n");
}

void loop(){
  const int valorLDR1 = analogRead(pinoLDR1);
  const int valorLDR2 = analogRead(pinoLDR2);

  if(debugMode) {
    char buffer[20];
    sprintf(buffer, "Sensor 1: %d\n Sensor 2: %d\n Threshold: %d\n", valorLDR1, valorLDR2, thresholdDoLDR);
    imprime(buffer);
    delay(1000);
  }

  // bolinha passou pelo sensor 1
  if(tempoQueABolinhaPassouNoLDR1 == 0 && valorLDR1 > thresholdDoLDR) {
    tempoQueABolinhaPassouNoLDR1 = millis();
    char buffer[40];
    sprintf(buffer, "Tempo no sensor 1: %lu\n", tempoQueABolinhaPassouNoLDR1);
    imprime(buffer);
  }

  // bolinha passou pelo sensor 2
  if(tempoQueABolinhaPassouNoLDR1 != 0 && tempoQueABolinhaPassouNoLDR2 == 0 && valorLDR2 > thresholdDoLDR) {
    tempoQueABolinhaPassouNoLDR2 = millis();
    char buffer[40];
    sprintf(buffer, "Tempo no sensor 2: %lu\n", tempoQueABolinhaPassouNoLDR2);
    imprime(buffer);
  }

  if(tempoQueABolinhaPassouNoLDR1 != 0 && tempoQueABolinhaPassouNoLDR2 != 0) {
    int tempoEntreSensoresEmMS = tempoQueABolinhaPassouNoLDR2 - tempoQueABolinhaPassouNoLDR1;

    char buffer[100];
    sprintf(buffer, "Tempo: %d ms\n", tempoEntreSensoresEmMS);
    imprime(buffer);

    tempoQueABolinhaPassouNoLDR1 = 0;
    tempoQueABolinhaPassouNoLDR2 = 0;
  }

  if(bluetooth.available()){
    int dadoBluetooth = bluetooth.read();

    if(dadoBluetooth == '1')
      debugMode = true;
    else if (dadoBluetooth == '0')
      debugMode = false;
    else if (dadoBluetooth == '2')
      thresholdDoLDR = 200;
    else if (dadoBluetooth == '3')
      thresholdDoLDR = 300;
    else if (dadoBluetooth == '4')
      thresholdDoLDR = 400;
    else if (dadoBluetooth == '5')
      thresholdDoLDR = 500;
    else if (dadoBluetooth == '6')
      thresholdDoLDR = 600;
    else if (dadoBluetooth == '7')
      thresholdDoLDR = 700;
    else if (dadoBluetooth == '8')
      thresholdDoLDR = 800;
    else if (dadoBluetooth == '9')
      thresholdDoLDR = 900;
  }
}

// Cabos
// Vermelho vai na de 3.3v
// Azul e preto vão na GND
// Marrom vai na 5v
// Verde vai na A2
// Amarelo vai na A3
// Branco vai na 10
// Cinza vai na 11
