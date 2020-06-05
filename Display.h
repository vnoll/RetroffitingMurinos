#ifndef __MURINOS__HEADER__
#define __MURINOS__HEADER__

#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>

#include <Fonts/FreeSans9pt7b.h>
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

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define LBLUE   0x7E7E
#define LGREEN  0XBFCF
#define KHAKI   0xF0E68C
#define GREY    0xFF6347
#define TOMATO  tft.color565(255, 69, 0)
#define GELO    tft.color565(240, 255, 240)
#define DBLUE   tft.color565(0, 0, 31)
#define TFT_MINX 10
#define TFT_MINY 10
#define TFT_MAXX 469
#define TFT_MAXY 309


#include "Display.h"
#include "Medidas.h"
MCUFRIEND_kbv tft;

// Funções de Menus
void Abertura();
void menuPrincipal();
void menuGenerico();
int menuTFA();
void changeMenu();
void printaparar();
void printabotao(int posicao);
void printaopcoes(int posicao);
// funcoes display
// ================

void showmsgf(int x, int y, int sz, uint16_t color,  const GFXfont *f, const char *txt, const char *msg);
void showmsg(int x, int y, int sz, uint16_t color,  const GFXfont *f, const char *msg);
void showint(int x, int y, int sz, uint16_t color,  const GFXfont *f, int t);
void showtempo(int x, int y, int sz, uint16_t color,  const GFXfont *f, int t);
unsigned long Lines(uint16_t color);
void ShowTempo();
void showVelocidade(int vel);
void ShowTempoTFA(long temp);

#endif
