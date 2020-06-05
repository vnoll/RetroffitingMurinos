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

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif


// Variaveis globais
static int pos =0;
int newPos = 0;
long newvelo, velo=0;
int selecionado = 0, primeiravez = 1;
int valor = 0, X;
char* modo;
char menu = principal; //Variávl para selecionar o menu
char pressbt; // flag para armazenar estado do botão
long NEWTEMPOTOTAL=0, TEMPOTOTAL=0;

#endif
