#ifndef __MAIN__HEADER__
#define __MAIN__HEADER__

#define principal 0
#define manual 1
#define tcfm 2
#define tfa 3
#define tfagenerico 4
#define confirma 3
#define changetempo 2
#define changevelocidade 1
#define ON 1
#define OFF 0
#define voltar 4
#define parar 3
#define iniciar 2
#define RESET 500

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif
#include "stdlib.h"
#include "stdio.h"

// Variaveis globais
static int pos =0;
int newPos = 0;
float newvelo, velo=0, distancia = 0, veloreal=0.1, oldvelocidade=0;
float oldDistanciatotal=0, distanciatotal = 0;
int selecionado = 0, primeiravez = 1, playtime=0;
int SELECIONAVELOCIDADE = 0,Y, X;
char* modo;
char ftemp;
char menu = principal; //Variávl para selecionar o menu
char BOTAOPRESSIONADO; // flag para armazenar estado do botão
long NEWTEMPOTOTAL=0, TEMPOTOTAL=0;

#endif
