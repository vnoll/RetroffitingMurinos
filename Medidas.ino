#include "Medidas.h"
#include "Main.h"


void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
    interruptCounter1s++;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void initTimer() {
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
    DadosEnsaio.distancia1s = (DadosEnsaio.velocidade/(float)3.6); 
    DadosEnsaio.distanciaAcumulada += DadosEnsaio.distancia1s;
    oldinterruptCounter1s = interruptCounter1s;    
  }
  
}

void ZeraTimer() {
  interruptCounter1s = 0;
  Counter1Min = 0;
  Counter1Hour = 0;
  DadosEnsaio.distancia1s = 0;
}

/*
void updateVelocidadeEsteira()  
{
    Serial.println("update velocidade");
    if (Serial.available() > 0)
    {
      String dadoLido = Serial.readString();
      DadosEnsaio.velocidade = dadoLido.toFloat()/1000;
      Serial.println(DadosEnsaio.velocidade);
    }
}
*/

// read --> https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/wdts.html
 
void updateTask_Velocidade(void * dummy)  
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = 1500;
  xLastWakeTime = xTaskGetTickCount();
  
  while (true)
  {
    vTaskDelayUntil( &xLastWakeTime, xFrequency );
    //Serial.println("task update ok");
    if (Serial.available() > 0)
    {
      String dadoLido = Serial.readString();
      DadosEnsaio.velocidade = dadoLido.toFloat()/1000.0;
      //Serial.println(DadosEnsaio.velocidade); 
  
    }
  }  
}