#ifndef __MEDIDAS__HEADER__
#define __MEDIDAS__HEADER__

#include "Main.h"
#include <RotaryEncoder.h> //Adicionado a biblioteca do encoder

/* Definições do botão giratório */

#define ENCODER_DT 34  //Posisão do Pino DT
#define ENCODER_CLK 39 //Posição do Pino CLK
#define ENTER 35       //Posição Pino Enter
#define timermaximo 43200

RotaryEncoder encoder(ENCODER_DT, ENCODER_CLK);

volatile int oldinterruptCounter1s = 0, interruptCounter1s = 0; //Usa volatite para que não aconteça interrupções
int Counter1Min = 0;
int Counter1Hour = 0;
int pos = 1;
int newPos = 1;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void initTimer();               //Função de inicialização do contador
void timerRefresh();            //Função de atualização do contador
void ZeraTimer();               //Função de resetar o contador
void updateDistancia();         //Função de atualização da distância em relação a velocidade
void updateVelocidadeEsteira(); //Função de controle de velocidade da esteira
void updateTask_Velocidade();   //Função de atualização e recebimento da velocidade atual através do Nano
void onOff();                   //Função de ligar e desligar o relé de acionamento



#endif
