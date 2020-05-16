#include "Display.h"

void showmsg(int x, int y, int sz, uint16_t color,  const GFXfont *f, const char *msg)
{
    tft.setFont(f);
    tft.setCursor(x, y);
    tft.setTextColor(color);
    tft.setTextSize(sz);
    tft.print(msg);
}

void showtempo(int x, int y, int sz, uint16_t color,  const GFXfont *f, int t)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.printf("%d", t);
}

unsigned long Lines(uint16_t color)
{
  unsigned long start, t;
  int           x1, y1, x2, y2,
                w = tft.width(),
                h = tft.height();

  tft.fillScreen(WHITE);

  x1 = y1 = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t     = micros() - start; // fillScreen doesn't count against timing

  tft.fillScreen(WHITE);

  x1    = w - 1;
  y1    = 0;
  y2    = h - 1;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(WHITE);

  x1    = 0;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = w - 1;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  t    += micros() - start;

  tft.fillScreen(WHITE);

  x1    = w - 1;
  y1    = h - 1;
  y2    = 0;
  start = micros();
  for (x2 = 0; x2 < w; x2 += 6) tft.drawLine(x1, y1, x2, y2, color);
  x2    = 0;
  for (y2 = 0; y2 < h; y2 += 6) tft.drawLine(x1, y1, x2, y2, color);

  return micros() - start;
}


// TCFM = Teste de condicionamento fisico maximo
void menuTCFM()
{
  showmsg(180, 40, 1, BLACK, &FreeSerifBold24pt7b, "TCFM");
  showmsg(40, 200, 1, BLACK, &FreeSansBold18pt7b, "Velocidade:");
  showmsg(40, 270, 1, BLACK, &FreeSansBold18pt7b, "Tempo: ");
  PLAY = 2;
  if (PLAY == 2)
  {
    ShowTempo();
  }
  switch (PLAY)
  {
    case 1:
      showmsg(280, 120, 1, BLACK, &FreeSerifBold18pt7b, "STOP");
      showmsg(100, 120, 1, RED, &FreeSerifBold18pt7b, "START");
      break;

    case 2:
      showmsg(280, 120, 1, RED, &FreeSerifBold18pt7b, "STOP");
      showmsg(100, 120, 1, BLACK, &FreeSerifBold18pt7b, "START");
      break;

  }
}

void showAbertura()
{
  Lines(CYAN);
  tft.fillScreen(LBLUE);
  showmsg(20, 160, 1, BLACK, &FreeSerifBold24pt7b, "Sistema de controle para Murinos");
  delay(500);
  showmsg(20, 240, 1, BLACK, &FreeSerifBold12pt7b, "Desenvolvido por: Laboratorio NERsD");
  showmsg(20, 280, 1, BLACK, &FreeSerifBold12pt7b, "Contato: vnoll@ifsc.edu.br");
  delay(2000);
  tft.fillScreen(LBLUE);
}

void menuprincipal()
{
  menu = 0;
  showmsg(80, 40, 1, BLACK, &FreeSerifBold24pt7b, "Menu Principal");
  showmsg(40, 130, 1, BLACK, &FreeSansBold12pt7b, "Modo MANUAL");
  showmsg(40, 200, 1, BLACK, &FreeSansBold12pt7b, "Modo TFCA");
  showmsg(40, 270, 1, BLACK, &FreeSansBold12pt7b, "Modo TFA");
  CURSOR = 2;
  switch (CURSOR)
  {
    case 1:
    tft.fillCircle(20, 122, 9, RED);
    tft.fillCircle(20, 192, 9, LBLUE);
    tft.fillCircle(20, 262, 9, LBLUE);
    break;
    
    case 2:
    tft.fillCircle(20, 122, 9, LBLUE);
    tft.fillCircle(20, 192, 9, RED);
    tft.fillCircle(20, 262, 9, LBLUE);
    break;

    case 3:
    tft.fillCircle(20, 122, 9, LBLUE);
    tft.fillCircle(20, 192, 9, LBLUE);
    tft.fillCircle(20, 262, 9, RED);
    break;
  }
  delay(5000);
  if(CURSOR==2)
  {
    tft.fillScreen(LBLUE);
    menu=2;
    while(menu==2)
    {
      menuTFA();
    }
  }
}

void menuPrincipal()
{

    showmsg(80, 40, 1, BLACK, &FreeSerifBold24pt7b, "Menu Principal");
    
    tft.drawRoundRect(142, 95, 462, 50, 5, WHITE);
    tft.fillRoundRect(142, 95, 462, 50, 5, GREEN);
    tft.setTextColor(BLACK);  
    tft.setTextSize(3);
    tft.setCursor(152, 110);
    tft.println("Modo MANUAL");

    tft.drawRoundRect(142, 155, 462, 50, 5, WHITE);
    tft.setTextColor(RED);  tft.setTextSize(3);
    tft.setCursor(152, 165);
    tft.println("Modo TFCA");

    tft.drawRoundRect(142, 215, 462, 50, 5, WHITE);
    tft.setTextColor(RED);  
    tft.setTextSize(3);
    tft.setCursor(152, 225);
    tft.println("Modo TFA");


}


// TFA =Treinamento Fisico Aerobio
void menuTFA()
{
  showmsg(200, 40, 1, BLACK, &FreeSerifBold24pt7b, "TFA");
  showmsg(40, 200, 1, BLACK, &FreeSansBold18pt7b, "Velocidade:");
  showmsg(40, 270, 1, BLACK, &FreeSansBold18pt7b, "Tempo: ");
  PLAY = 2;
  if (PLAY == 2)
  {
    ShowTempo();
  }
  switch (PLAY)
  {
    case 1:
      showmsg(280, 120, 1, BLACK, &FreeSerifBold18pt7b, "STOP");
      showmsg(100, 120, 1, RED, &FreeSerifBold18pt7b, "START");
      break;
    
    case 2:
      showmsg(280, 120, 1, RED, &FreeSerifBold18pt7b, "STOP");
      showmsg(100, 120, 1, BLACK, &FreeSerifBold18pt7b, "START");
      break;
    
  }
}

void ShowTempo()
{
	int seg1,seg2;
	int min1,min2;
	int hora1,hora2;
 
  static int oldseg1=0,oldseg2=0;
  static int oldmin1=0,oldmin2=0;
  static int oldhora1=0,oldhora2=0;

  static int flag_primeira_vez = 1;
	
	seg1=((interruptCounter1s%60)%10);
	seg2=((interruptCounter1s%60)/10);
	min1=((interruptCounter1s/60)%10);
	min2=((interruptCounter1s/60)/10);
	hora1 = ((Counter1Min/60)%10);
	hora2 = ((Counter1Min/60)/10); 

  if (flag_primeira_vez == 1)
  {
      showtempo(310, 270, 1, BLACK, &FreeSansBold18pt7b, seg1);
      showtempo(290, 270, 1, BLACK, &FreeSansBold18pt7b, seg2);
      showmsg(280, 270, 1, BLACK, &FreeSansBold18pt7b, ":");
      showtempo(260, 270, 1, BLACK, &FreeSansBold18pt7b, min1);
      showtempo(240, 270, 1, BLACK, &FreeSansBold18pt7b, min2);
      showmsg(220, 270, 1, BLACK, &FreeSansBold18pt7b, ":");
      showtempo(200, 270, 1, BLACK, &FreeSansBold18pt7b, hora1);
      showtempo(180, 270, 1, BLACK, &FreeSansBold18pt7b, hora2);

      oldseg1 = seg1;
      oldseg2 = seg2;
      oldmin1 = min1;
      oldmin2 = min2;
      oldhora1 = hora1;
      oldhora2 = hora2;
      flag_primeira_vez = 0;
  }

  if (((seg1 != oldseg1) || (seg2 != oldseg2)) && (flag_primeira_vez == 0))
  {  
      // apaga os numeros anteriores somente se nao for a primeira vez
      showtempo(310, 270, 1, LBLUE, &FreeSansBold18pt7b, oldseg1);
      showtempo(290, 270, 1, LBLUE, &FreeSansBold18pt7b, oldseg2);
      showtempo(260, 270, 1, LBLUE, &FreeSansBold18pt7b, oldmin1);
      showtempo(240, 270, 1, LBLUE, &FreeSansBold18pt7b, oldmin2);
      showtempo(200, 270, 1, LBLUE, &FreeSansBold18pt7b, oldhora1);
      showtempo(180, 270, 1, LBLUE, &FreeSansBold18pt7b, oldhora2);

      // escreve os novos
    	showtempo(310, 270, 1, BLACK, &FreeSansBold18pt7b, seg1);
    	showtempo(290, 270, 1, BLACK, &FreeSansBold18pt7b, seg2);
    	showmsg(280, 270, 1, BLACK, &FreeSansBold18pt7b, ":");
    	showtempo(260, 270, 1, BLACK, &FreeSansBold18pt7b, min1);
    	showtempo(240, 270, 1, BLACK, &FreeSansBold18pt7b, min2);
    	showmsg(220, 270, 1, BLACK, &FreeSansBold18pt7b, ":");
    	showtempo(200, 270, 1, BLACK, &FreeSansBold18pt7b, hora1);
    	showtempo(180, 270, 1, BLACK, &FreeSansBold18pt7b, hora2);

      // atualiza 
      oldseg1 = seg1;
      oldseg2 = seg2;
      oldmin1 = min1;
      oldmin2 = min2;
      oldhora1 = hora1;
      oldhora2 = hora2;

  }
 
 }
