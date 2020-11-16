
#define DEBUG 1

int interrupt = 0; //Pino ligado ao pino D2 do sensor
float rpm;
float pulsos;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;

//Altere o numero abaixo de acordo com o seu disco encoder
unsigned int pulsos_por_volta = 1000;

void contador()
{ //Incrementa contador
  pulsos++;
}

void setup()
{
  Serial.begin(9600);
  startMillis = millis(); // variável recebe o valor inicial de tempo do processador
  //Interrupcao 0 - pino digital 2
  //Aciona o contador a cada pulso
  attachInterrupt(interrupt, contador, RISING);
  rpm = 0;
  pulsos = 0;
}
void loop()
{
  currentMillis = millis(); //variável de tempo atual recebe o tempo real do contador
  if (currentMillis - startMillis >= period)
  {
    detachInterrupt(interrupt); // desativa a interrupção para cálculos
    rpm = (60 * pulsos / pulsos_por_volta ); // cálculo de conversão para RPM
    Serial.print(rpm);
    Serial.print("\n");
    startMillis = currentMillis; //tempo antigo recebe o tempo atual

    #if DEBUG
      if (pulsos >= 60000.0) pulsos =100.0;
      pulsos += 100.0; 
    #endif
    
    #if !DEBUG
      //zera os pulsos para recomeçar a contagem
      pulsos = 0;
    #endif

    attachInterrupt(interrupt, contador, RISING); // reativa a interrupção
  }
}
