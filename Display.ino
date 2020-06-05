#include "Display.h"
void ShowTempoTFA(long temp)
{
  long seg1,seg2;
  long min1,min2;
  long hora1,hora2;
  long countermin;
  static long oldseg1=0,oldseg2=0;
  static long oldmin1=0,oldmin2=0;
  static long oldhora1=0,oldhora2=0;
  
  seg1=((temp%60)%10);
  seg2=((temp%60)/10);
  min1=((temp/60)%10);
  min2=((temp/60)/10);
  if (temp >= 60)
  {
    countermin++;
    if (countermin == 60)  
    {
      countermin = 0;
      Counter1Hour++;
      if (Counter1Hour > 11) 
      {
        Counter1Hour = 0;
      }
    }
  }
  hora1 = ((countermin/60)%10);
  hora2 = ((countermin/60)/10); 

  if (primeiravez)
  {
    showtempo(435, 215, 1, BLACK, &FreeSansBold18pt7b, seg1);
    showtempo(415, 215, 1, BLACK, &FreeSansBold18pt7b, seg2);
    showmsg(405, 213, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(385, 215, 1, BLACK, &FreeSansBold18pt7b, min1);
    showtempo(365, 215, 1, BLACK, &FreeSansBold18pt7b, min2);
    showmsg(355, 213, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(335, 215, 1, BLACK, &FreeSansBold18pt7b, hora1);
    showtempo(315, 215, 1, BLACK, &FreeSansBold18pt7b, hora2);

    oldseg1 = seg1;
    oldseg2 = seg2;
    oldmin1 = min1;
    oldmin2 = min2;
    oldhora1 = hora1;
    oldhora2 = hora2;
    primeiravez=0;
  }

  if (((seg1 != oldseg1) || (seg2 != oldseg2)) && (primeiravez == 0))
  {
    // apaga os numeros anteriores somente se nao for a primeira vez
    showtempo(435, 215, 1, LGREEN, &FreeSansBold18pt7b, oldseg1);
    showtempo(415, 215, 1, LGREEN, &FreeSansBold18pt7b, oldseg2);
    showtempo(385, 215, 1, LGREEN, &FreeSansBold18pt7b, oldmin1);
    showtempo(365, 215, 1, LGREEN, &FreeSansBold18pt7b, oldmin2);
    showtempo(335, 215, 1, LGREEN, &FreeSansBold18pt7b, oldhora1);
    showtempo(315, 215, 1, LGREEN, &FreeSansBold18pt7b, oldhora2);
    //escreve os novos
    showtempo(435, 215, 1, BLACK, &FreeSansBold18pt7b, seg1);
    showtempo(415, 215, 1, BLACK, &FreeSansBold18pt7b, seg2);
    showmsg(405, 213, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(385, 215, 1, BLACK, &FreeSansBold18pt7b, min1);
    showtempo(365, 215, 1, BLACK, &FreeSansBold18pt7b, min2);
    showmsg(355, 213, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(335, 215, 1, BLACK, &FreeSansBold18pt7b, hora1);
    showtempo(315, 215, 1, BLACK, &FreeSansBold18pt7b, hora2);

    // atualiza
    oldseg1 = seg1;
    oldseg2 = seg2;
    oldmin1 = min1;
    oldmin2 = min2;
    oldhora1 = hora1;
    oldhora2 = hora2;
  }
}
void showVelocidade(int vel)
{
  static int oldvelocidade;
  if(primeiravez)
  {
    showint(365, 145, 1, BLACK, &FreeSansBold18pt7b, vel);
    oldvelocidade = vel;
    primeiravez=0;
  }
  if(vel!= oldvelocidade && primeiravez==0)
  {
    showint(365, 145, 1, LGREEN, &FreeSansBold18pt7b, oldvelocidade);
    showint(365, 145, 1, BLACK, &FreeSansBold18pt7b, vel);
    oldvelocidade = vel;
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

  if (primeiravez == 1)
  {
      showint(435, 235, 1, BLACK, &FreeSansBold18pt7b, seg1);
      showint(415, 235, 1, BLACK, &FreeSansBold18pt7b, seg2);
      showmsg(405, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
      showint(385, 235, 1, BLACK, &FreeSansBold18pt7b, min1);
      showint(365, 235, 1, BLACK, &FreeSansBold18pt7b, min2);
      showmsg(355, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
      showint(335, 235, 1, BLACK, &FreeSansBold18pt7b, hora1);
      showint(315, 235, 1, BLACK, &FreeSansBold18pt7b, hora2);

      oldseg1 = seg1;
      oldseg2 = seg2;
      oldmin1 = min1;
      oldmin2 = min2;
      oldhora1 = hora1;
      oldhora2 = hora2;
      primeiravez= 0;
  }

  if (((seg1 != oldseg1) || (seg2 != oldseg2)) && (primeiravez == 0))
  {  
      // apaga os numeros anteriores somente se nao for a primeira vez
      showint(435, 235, 1, GELO, &FreeSansBold18pt7b, oldseg1);
      showint(415, 235, 1, GELO, &FreeSansBold18pt7b, oldseg2);
      showint(385, 235, 1, GELO, &FreeSansBold18pt7b, oldmin1);
      showint(365, 235, 1, GELO, &FreeSansBold18pt7b, oldmin2);
      showint(335, 235, 1, GELO, &FreeSansBold18pt7b, oldhora1);
      showint(315, 235, 1, GELO, &FreeSansBold18pt7b, oldhora2);

      // escreve os novos
      showint(435, 235, 1, BLACK, &FreeSansBold18pt7b, seg1);
      showint(415, 235, 1, BLACK, &FreeSansBold18pt7b, seg2);
      showmsg(405, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
      showint(385, 235, 1, BLACK, &FreeSansBold18pt7b, min1);
      showint(365, 235, 1, BLACK, &FreeSansBold18pt7b, min2);
      showmsg(355, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
      showint(335, 235, 1, BLACK, &FreeSansBold18pt7b, hora1);
      showint(315, 235, 1, BLACK, &FreeSansBold18pt7b, hora2);

      // atualiza 
      oldseg1 = seg1;
      oldseg2 = seg2;
      oldmin1 = min1;
      oldmin2 = min2;
      oldhora1 = hora1;
      oldhora2 = hora2;

  }
 }
void showmsg(int x, int y, int sz, uint16_t color,  const GFXfont * f, const char *msg)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.print(msg);
}

void showmsgf(int x, int y, int sz, uint16_t color,  const GFXfont * f, const char *txt, const char *msg)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.print(txt);
  tft.printf("%s", msg);
}
void showtempo(int x, int y, int sz, uint16_t color,  const GFXfont * f, long t)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.printf("%ld", t);
}
void showint(int x, int y, int sz, uint16_t color,  const GFXfont * f, int t)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.printf("%d", t);
}

void Abertura()
{
  tft.fillScreen(LGREEN);
  showmsg(60, 40, 1, BLACK, &FreeSerifBold18pt7b, "SISTEMA DE TESTES");
  tft.drawFastHLine(60, 45, 355, BLACK);
  showmsg(90, 80, 1, BLACK, &FreeSerifBold18pt7b, "ERGOMETRICOS");
  tft.drawFastHLine(90, 85, 290, BLACK);
  showmsg(107, 120, 1, BLACK, &FreeSerifBold18pt7b, "PARA ANIMAIS");
  tft.drawFastHLine(107, 125, 260, BLACK);
  showmsg(110, 160, 1, BLACK, &FreeSerif18pt7b, "Desenvolvido pelo ");
  showmsg(55, 200, 1, BLACK, &FreeSerif18pt7b, "IFSC - Mecatronica - FLN");
  showmsg(250, 300, 1, BLACK, &FreeSerifBold18pt7b, "UDESC/2020");
  showmsg(40, 240, 1, BLACK, &FreeSerifBold12pt7b, "Edwan Seiki Kuwakino");
  showmsg(40, 260, 1, BLACK, &FreeSerifBold12pt7b, "Lucas Terres Hoffmann");
  showmsg(40, 280, 1, BLACK, &FreeSerifBold12pt7b, "Valdir Noll");
  delay(5000);
}
