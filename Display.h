#ifndef __MURINOS__HEADER__
#define __MURINOS__HEADER__

#include <Adafruit_GFX.h>  //Inclusão biblioteca LCD
#include <MCUFRIEND_kbv.h> //Biblioteca referente ao touchscreen

#include "Main.h"

MCUFRIEND_kbv tft;

#include <Fonts/FreeSans9pt7b.h> //Importação das fontes
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSans18pt7b.h>
#include <Fonts/FreeSans24pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/FreeSansBold18pt7b.h>
#include <Fonts/FreeSansBold24pt7b.h>
#include <Fonts/FreeSerif12pt7b.h>
#include <Fonts/FreeSerif18pt7b.h>
#include <Fonts/FreeSerifBold9pt7b.h>
#include <Fonts/FreeSerifBold12pt7b.h>
#include <Fonts/FreeSerifBold18pt7b.h>
#include <Fonts/FreeSerifBold24pt7b.h>
#include <FreeDefaultFonts.h>

#define BLACK 0x0000 //Definição das cores em hexa
#define BLUE 0x001F


#define WHITE 0xFFFF
#define LBLUE 0x7E7E
#define LGREEN 0XBFCF
#define KHAKI 0xF0E68C
#define GREY 0xFF6347
#define DORANGE tft.color565(255, 140, 0) //Cores do próprio LCD
#define TOMATO tft.color565(255, 69, 0)
#define GELO tft.color565(240, 255, 240)
#define DBLUE tft.color565(0, 0, 31)
#define TFT_MINX 10 //definição dos pontos máximos e mínimos do LCD
#define TFT_MINY 10
#define TFT_MAXX 469
#define TFT_MAXY 309


// variaveis globais deste modulo
bool primeiravez_showDistancia = true; //Flag primeiravez
bool primeiravez_showVelocidadeReal = true;
bool primeiravez_showVelocidadeDefinida = true;
bool primeiravez_ShowTempoConfig = true;
bool primeiravez_ShowTempo = true;

// Funções do Display
/*************************/
void showDistanciaOld();                              //Função distancia inicial
void showDistancia(float distancia);                  //Função distancia atual
void showVelocidadeReal(int x, int y, float vel);     //Função velocidade instantânea
void showVelocidadeDefinida(int x, int y, float vel); //Função velocidade configurada
void ShowTempoConfig(long TEMPOTOTAL);
void showTelaModoManual(int X, char *titulo);
void ShowOpcoesModoManual();
void showTelaModoTCFM(int X, char *titulo);
void ShowOpcoesModoTCFM();
void showTelaModoTFA(int X, char *titulo);
void ShowOpcoesModoTFA();
void ShowTempo(long numinter);
void showtempo(int x, int y, int sz, uint16_t color, const GFXfont *f, long t); //Mostra as informações desejadas, com sua posição, tamanho de fonte, cor.
void showmsg(int x, int y, int sz, uint16_t color, const GFXfont *f, const char *msg);
void showmsgf(int x, int y, int sz, uint16_t color, const GFXfont *f, const char *txt, const char *msg);
void showint(int x, int y, int sz, uint16_t color, const GFXfont *f, int t);
void showfloat(int x, int y, int sz, uint16_t color, const GFXfont *f, float t);
void showdist(int x, int y, int sz, uint16_t color, const GFXfont *f, float t);
void showAbertura();
void PrintDataSERIAL4Debug();

#endif
