#include "Medidas.h"
#include "Main.h"

void IRAM_ATTR onTimer()
{
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter1s++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void initTimer()
{
  interruptCounter1s = 0;
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

void updateDistancia()
{
  if (oldinterruptCounter1s != interruptCounter1s)
  {
    DadosEnsaio.distancia1s = (DadosEnsaio.velocidade / (float)3.6);
    DadosEnsaio.distanciaAcumulada += DadosEnsaio.distancia1s;
    oldinterruptCounter1s = interruptCounter1s;
  }
}

void ZeraTimer()
{
  interruptCounter1s = 0;
  Counter1Min = 0;
  Counter1Hour = 0;
  DadosEnsaio.distancia1s = 0;
}

/* Função de atualização da velocidade da esteira em relação com a velocidade atual */
void updateVelocidadeEsteira()
{

  float offset = 0.10;
  float offset2 = 0.03;

  switch (Velocidade)
  {
  case aumentarVelocidade:

    digitalWrite(menosVelo, LOW);

    if (millis() - tempoState < 200)
    {
      digitalWrite(maisVelo, HIGH);
    }
    else
    {
      digitalWrite(maisVelo, LOW);
    }

    if (millis() - tempoState > 700)
    {
      tempoState = millis();
    }

    if ((DadosEnsaio.config_velocidade - offset2) <= DadosEnsaio.velocidade || DadosEnsaio.velocidade == DadosEnsaio.config_velocidade)
    {
      flagFuncionamento = false;
      Velocidade = mesmaVelocidade;
    }
    if (DadosEnsaio.velocidade > (DadosEnsaio.config_velocidade + offset))
    {
      flagFuncionamento = false;
      Velocidade = diminuirVelocidade;
    }

    break;

  case diminuirVelocidade:
    digitalWrite(maisVelo, LOW);
    flagFuncionamento = false;
    if (millis() - tempoState < 200)
    {
      digitalWrite(menosVelo, HIGH);
    }
    else
    {
      digitalWrite(menosVelo, LOW);
    }

    if (millis() - tempoState > 700)
    {
      tempoState = millis();
    }
    if (DadosEnsaio.config_velocidade == DadosEnsaio.velocidade || DadosEnsaio.velocidade <= (DadosEnsaio.config_velocidade + offset2))

    {
      flagFuncionamento = false;
      Velocidade = mesmaVelocidade;
    }
    if (DadosEnsaio.velocidade < (DadosEnsaio.config_velocidade - offset))
    {
      Velocidade = aumentarVelocidade;
    }

    break;

  case mesmaVelocidade:
  {
    digitalWrite(menosVelo, LOW);
    digitalWrite(maisVelo, LOW);
    flagFuncionamento = false;
    if (millis() - tempoState < 200)
    {
      digitalWrite(menosVelo, LOW);
      digitalWrite(maisVelo, LOW);
    }
    else
    {
      digitalWrite(menosVelo, LOW);
      digitalWrite(maisVelo, LOW);
    }

    if (millis() - tempoState > 700)
    {
      tempoState = millis();
    }

    if (DadosEnsaio.velocidade > (DadosEnsaio.config_velocidade + offset))
    {
      Velocidade = diminuirVelocidade;
    }
    if (DadosEnsaio.velocidade < (DadosEnsaio.config_velocidade - offset))
    {
      Velocidade = aumentarVelocidade;
    }
    break;
  }
  }
  if (flagFuncionamento == true)
  {
    if (DadosEnsaio.config_velocidade > DadosEnsaio.velocidade)
    {
      Velocidade = aumentarVelocidade;
    }
  }
}

/* Função de atualização da velocidade recebendo via serial do Arduino Nano */
 /* void updateTask_Velocidade(void *dummy)
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 500;
  xLastWakeTime = xTaskGetTickCount();

  while (true)
  {

    vTaskDelayUntil(&xLastWakeTime, xFrequency);

    /*
    if (Serial1.available() > 0)
    {
      delay(5);
      byte buf[4];
      byte *bp = buf;
      while (Serial1.available())
      {
        *bp = Serial1.read();
        if (bp - buf < 3)
          bp++;
      }
      float received = *(float *)buf;
      DadosEnsaio.velocidade = received;
    }
  }
  

    RPM = contador_pulso / 1000.00 * 60.00;
    speedkmh = ((1.000 * RPM * 0.1885 * 0.051) * 0.665);
    DadosEnsaio.velocidade = speedkmh;
  }
}

*/

void encoderPinoB()
{
  static char flag = 0;
  static char numPeriodsToSendSerial = 0;
   contador_pulso++;
   if (flag == 0) {digitalWrite(encoder_b2, HIGH); flag =1;}
   else {digitalWrite(encoder_b2, LOW); flag =0;}

  if (micros() - lastTime >= 100000)
  {    
    numPeriodsToSendSerial++;
    // calcula o valor da velocidade baseada no numero de pulsos em 100ms
    //RPM = contador_pulso / 1000.00 * 60.00;
    //speedkmh = ((1.000 * RPM * 0.1885 * 0.051) * 0.665);

    //Serial.println(contador_pulso);
    
    //RPM = (contador_pulso/1000.00)*2.0*3.141516*25.50;
    //speedkmh = (RPM/1000.00)*3.6*52.00/160.00*10;
    speedkmh = contador_pulso*0.0018745;
    DadosEnsaio.velocidade = speedkmh;

    lastTime = micros();
    contador_pulso = 0;

    if (numPeriodsToSendSerial >=30)
    {
        Serial.println(DadosEnsaio.velocidade);
        numPeriodsToSendSerial = 0;
    }    
  }
}


void onOff()
{
  if (flagOn == true)
  {
    digitalWrite(botaoEmergencia, LOW);
  }
  if (flagOn == false)
  {
    digitalWrite(botaoEmergencia, HIGH);
  }

  return;
}