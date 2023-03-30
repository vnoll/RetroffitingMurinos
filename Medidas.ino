#include "Medidas.h"
#include "Main.h"

// veja em 
// https://deepbluembedded.com/esp32-timers-timer-interrupt-tutorial-arduino-ide/

void IRAM_ATTR onTimer0_ISR()
{
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter1s++;
  //speedkmh = contador_pulso * 0.00018385385;
  //DadosEnsaio.velocidade = speedkmh;
  //contador_pulso = 0;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void initTimer0()
{
  interruptCounter1s = 0;
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer0_ISR, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}

// timer de 100ms para medir a velocidade
void IRAM_ATTR onTimer1Velo_ISR()
{
  // multiplica por 10 para ter o numero de contagens que teria
  // em 1 segundo
  contador_pulso=contador_pulso * 10;
  speedkmh = contador_pulso * 0.00018385385;
  DadosEnsaio.velocidade = speedkmh;
  contador_pulso = 0;

}

void initTimer1Velo()
{
  timer1Velo = timerBegin(1, 80, true);
  timerAttachInterrupt(timer1Velo, &onTimer1Velo_ISR, true);
  timerAlarmWrite(timer1Velo, 100000, true);
  timerAlarmEnable(timer1Velo);
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

int updateVelocidadeEsteira()
{
  float histerese = 0.05;
  if (DadosEnsaio.velocidade < (DadosEnsaio.config_velocidade-histerese))
  {
    digitalWrite(maisVelo, HIGH);
    digitalWrite(menosVelo, LOW);
    return 0;   
  }
  else
  {
    if (DadosEnsaio.velocidade > (DadosEnsaio.config_velocidade+histerese))
    {
      digitalWrite(maisVelo, LOW);
      digitalWrite(menosVelo, HIGH);
      return 0;
    }
    else
    {
      digitalWrite(maisVelo, LOW);
      digitalWrite(menosVelo, LOW);
    }
  }
  
}


/*
int updateVelocidadeEsteira()
{
  float erro = 0;
  erro = DadosEnsaio.config_velocidade - DadosEnsaio.velocidade;
  
  if ( (erro >= -2.0) && (erro <= 2.0) )
    {
       // a velocidade não precisa mudar --- eh a mesma
       digitalWrite(menosVelo, LOW);
       digitalWrite(maisVelo, LOW);
       tempoState = millis();
    }
    else
    {      
      if (erro > 2.0)
      {
        // aumenta a velocidade
		
		    if ((erro > 50.0) && (DadosEnsaio.config_velocidade > 1.0))
		    {
			    digitalWrite(maisVelo, HIGH);
			    tempoState = millis();
		    }
		    else
		    {
			    if (millis()-tempoState>0 && millis()-tempoState<=TON)
			    {
				    digitalWrite(menosVelo, LOW);
				    digitalWrite(maisVelo, HIGH);
			    }
			    if (millis()-tempoState > TON) {digitalWrite(maisVelo, LOW); digitalWrite(menosVelo, LOW);}
			    if (millis()-tempoState > TOFF) tempoState = millis();			
		    }		
      }
      else
      {
        if (erro < -2.0)
          {
            // diminui a velocidade
            if ((erro < -50.0) && (DadosEnsaio.config_velocidade > 1.0))
            {
              digitalWrite(menosVelo, HIGH);
              tempoState = millis();
            }
          }
          else
          {
            if (millis()-tempoState>0 && millis()-tempoState<=TON)
            {
              digitalWrite(maisVelo, LOW);
              digitalWrite(menosVelo, HIGH);
            }			
            if (millis()-tempoState > TON) {digitalWrite(menosVelo, LOW);digitalWrite(maisVelo, LOW);}
            if (millis()-tempoState > TOFF) tempoState = millis();;
          }
      }
   }  
}
*/

/*
void updateVelocidadeEsteira()
{
  float offset = 0.10;
  float offset2 = 0.05;
  float _erro = 0.80;

  if ((DadosEnsaio.velocidade >= DadosEnsaio.config_velocidade - offset2) && (DadosEnsaio.velocidade <= DadosEnsaio.config_velocidade + offset2))
    {
       // a velocidade não precisa mudar --- eh a mesma
       digitalWrite(menosVelo, LOW);
       digitalWrite(maisVelo, LOW);
       tempoState = millis();
    }
    else
    {      
      if ( DadosEnsaio.velocidade < (DadosEnsaio.config_velocidade + offset) )
      {
        // aumenta a velocidade
		
		    if (DadosEnsaio.velocidade < (_erro * DadosEnsaio.config_velocidade) && (DadosEnsaio.config_velocidade > 1.0))
		    {
			    digitalWrite(maisVelo, HIGH);
          digitalWrite(menosVelo, LOW);
			    tempoState = millis();
		    }
		    else
		    {
			    if (millis()-tempoState>0 && millis()-tempoState<=TON)
			    {
				    digitalWrite(menosVelo, LOW);
				    digitalWrite(maisVelo, HIGH);
			    }
			    if (millis()-tempoState > TON) {digitalWrite(maisVelo, LOW); digitalWrite(menosVelo, LOW);}
			    if (millis()-tempoState > TOFF) tempoState = millis();			
		    }		
      }
      else
      {
        if (DadosEnsaio.velocidade > (DadosEnsaio.config_velocidade - offset))
        {
          // diminui a velocidade
          if (DadosEnsaio.velocidade > (_erro * DadosEnsaio.config_velocidade) && (DadosEnsaio.config_velocidade > 1.0))
          {
            digitalWrite(menosVelo, HIGH);
            digitalWrite(maisVelo, LOW);
            tempoState = millis();
          }
          else
          {
            if (millis()-tempoState>0 && millis()-tempoState<=TON)
            {
              digitalWrite(maisVelo, LOW);
              digitalWrite(menosVelo, HIGH);
            }			
            if (millis()-tempoState > TON) {digitalWrite(menosVelo, LOW);digitalWrite(maisVelo, LOW);}
            if (millis()-tempoState > TOFF) tempoState = millis();;
          }
      }
    }
  }  
}
*/

/* Função de atualização da velocidade da esteira em relação com a velocidade atual 
void updateVelocidadeEsteira()
{

  float offset = 0.10;
  float offset2 = 0.03;

  switch (Velocidade)
  {
  case aumentarVelocidade:

    if (DadosEnsaio.config_velocidade * 0.7 > DadosEnsaio.velocidade && DadosEnsaio.config_velocidade > 1.0)
    {
      digitalWrite(menosVelo, LOW);
      digitalWrite(maisVelo, HIGH);
    }
    else
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

  if (DadosEnsaio.config_velocidade * 0.7 < DadosEnsaio.velocidade)
    {
      digitalWrite(menosVelo, HIGH);
      digitalWrite(maisVelo, LOW);
    }
    else
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
*/



/* Função de atualização da velocidade recebendo via serial do Arduino Nano 

NÃO É MAIS UTILIZADA...

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
   RPM = contador_pulso / 1000.00 * 60.00;
   speedkmh = ((1.000 * RPM * 0.1885 * 0.051) * 0.665);
   DadosEnsaio.velocidade = speedkmh;
 {
}
*/

//Função de atualização da velocidade baseado nos numero de pulsos em certo tempo

/*
void updateTask_Velocidade(void *dummy)
{
 TickType_t xLastWakeTime;
 const TickType_t xFrequency = 100;
 xLastWakeTime = xTaskGetTickCount();
 while (true)
 {
   vTaskDelayUntil(&xLastWakeTime, xFrequency);
    // Calcula o valor da velocidade baseada no numero de pulsos em 100ms
    //RPM = (contador_pulso/1000.00)*2.0*3.141516*25.50;
    //speedkmh = (RPM/1000.00)*3.6*52.00/160.00*10; 
    speedkmh = contador_pulso * 0.0018385385;
    DadosEnsaio.velocidade = speedkmh;
    contador_pulso = 0; 
  }
}
*/

// a cada pulso do encoder, ocorre uma interrupcao, que chama essa funçao
// a velocidade eh calculada a cada 1 seg
void encoderPinoB()
{
  contador_pulso++;
}

/*
void encoderPinoB()
{
  static char flag = 0;
  static char numPeriodsToSendSerial = 0;
  
  if (flag == 0)
  {
    digitalWrite(encoder_b2, HIGH);
    flag = 1;
  }
  else
  {
    digitalWrite(encoder_b2, LOW);
    flag = 0;
  }

  if (micros() - lastTime >= 100000)
  {
    numPeriodsToSendSerial++;

   // Calcula o valor da velocidade baseada no numero de pulsos em 100ms
    // RPM = (contador_pulso/1000.00)*2.0*3.141516*25.50;
    // speedkmh = (RPM/1000.00)*3.6*52.00/160.00*10;

    speedkmh = contador_pulso * 0.0018385385;
    DadosEnsaio.velocidade = speedkmh;

    lastTime = micros();
    contador_pulso = 0;

    if (numPeriodsToSendSerial >= 30)
    {
      //Serial.println(DadosEnsaio.velocidade);
      numPeriodsToSendSerial = 0;
    }
  }  
}
*/
void onOff()
{
  if (flagOn == true)
  {
    digitalWrite(botaoEmergencia, LOW);
    delay(100);
    digitalWrite(botaoEmergencia, LOW);
  }
  if (flagOn == false)
  {
    digitalWrite(botaoEmergencia, HIGH);
    delay(100);
    digitalWrite(botaoEmergencia, HIGH);
  }
}