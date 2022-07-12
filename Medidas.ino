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
  float offset2 = 0.01;

  switch (Velocidade)
  {
  case aumentarVelocidade:

    digitalWrite(menosVelo,LOW);

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

    if  ((DadosEnsaio.config_velocidade - offset2) <= DadosEnsaio.velocidade || DadosEnsaio.velocidade == DadosEnsaio.config_velocidade)
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
    digitalWrite(maisVelo,LOW);
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
    digitalWrite(menosVelo,LOW);
    digitalWrite(maisVelo,LOW);
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
void updateTask_Velocidade(void *dummy)
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 500;
  xLastWakeTime = xTaskGetTickCount();

  while (true)
  {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
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
}

void onOff()
{
  if(flagOn == true)
  {
    digitalWrite (botaoEmergencia, LOW);
  }
  if(flagOn == false)
  {
    digitalWrite (botaoEmergencia, HIGH);
  }

  return;
}