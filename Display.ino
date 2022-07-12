#include "Display.h"
#include "Medidas.h"

void showDistanciaOld(float distancia) //Mostra a distância
{
  static float oldDistancia = 0;
  if (oldDistancia != distancia) //Comparação de distância
  {
    // Limpa a tela da distancia e atualiza para a nova
    tft.fillRoundRect(306, 56, 78, 53, 8, GELO);
    showdist(317, 165, 1, BLACK, &FreeSansBold18pt7b, distancia); //Mostra a atual
    oldDistancia = distancia;                                     //Primeira recebe atual
  }
}

void showDistancia(float distancia) //Função de atualização da distância display
{
  static bool primeiravez = true; //Flag primeiravez
  static float oldDistanciatotal = 0;
  updateDistancia();
  if (primeiravez)
  {
    showdist(317, 165, 1, BLACK, &FreeSansBold18pt7b, distancia);
    oldDistanciatotal = distancia;
    primeiravez = false;
  }
  if (oldDistanciatotal != distancia)
  {
    showdist(317, 165, 1, GELO, &FreeSansBold18pt7b, oldDistanciatotal);
    showdist(317, 165, 1, BLACK, &FreeSansBold18pt7b, distancia);
    oldDistanciatotal = distancia;
  }
}

void showVelocidadeReal(int x, int y, float vel) //Função atualização velocidade display
{
  static bool primeiravez = true;
  static float oldvelocidade;
  if (primeiravez)
  {
    showfloat(x, y, 1, BLACK, &FreeSansBold18pt7b, vel);
    oldvelocidade = vel;
    primeiravez = false;
  }
  if (vel != oldvelocidade && primeiravez == false)
  {
    showfloat(x, y, 1, GELO, &FreeSansBold18pt7b, oldvelocidade);
    showfloat(x, y, 1, BLACK, &FreeSansBold18pt7b, vel);
    oldvelocidade = vel;
  }
}

void showVelocidadeDefinida(int x, int y, float vel) //Função atualização velocidade configurada display
{
  static float oldvelocidade;
  static bool primeiravez = true;
  if (primeiravez)
  {
    showfloat(x, y, 1, BLACK, &FreeSansBold18pt7b, vel);
    oldvelocidade = vel;
    primeiravez = false;
  }
  if (vel != oldvelocidade && primeiravez == false)
  {
    showfloat(x, y, 1, LGREEN, &FreeSansBold18pt7b, oldvelocidade);
    showfloat(x, y, 1, BLACK, &FreeSansBold18pt7b, vel);
    oldvelocidade = vel;
  }
}

void ShowOpcoes() //Opções de comando
{
  switch (comando)
  {
  case INICIAR:
    tft.drawRoundRect(35, 262, 122, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(36, 263, 120, 38, 8, TOMATO);
    showmsg(50, 290, 1, GELO, &FreeSansBold12pt7b, "INICIAR");
    tft.drawRoundRect(175, 262, 117, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(176, 263, 115, 38, 8, GREY);
    showmsg(190, 290, 1, GELO, &FreeSansBold12pt7b, "PARAR");
    tft.drawRoundRect(310, 262, 132, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(311, 263, 130, 38, 8, GREY);
    showmsg(325, 290, 1, GELO, &FreeSansBold12pt7b, "VOLTAR");
    break;

  case PARAR:
    tft.drawRoundRect(35, 262, 122, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(36, 263, 120, 38, 8, GREY);
    showmsg(50, 290, 1, GELO, &FreeSansBold12pt7b, "INICIAR");
    tft.drawRoundRect(175, 262, 117, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(176, 263, 115, 38, 8, TOMATO);
    showmsg(190, 290, 1, GELO, &FreeSansBold12pt7b, "PARAR");
    tft.drawRoundRect(310, 262, 132, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(311, 263, 130, 38, 8, GREY);
    showmsg(325, 290, 1, GELO, &FreeSansBold12pt7b, "VOLTAR");
    break;

  case VOLTAR:
    tft.drawRoundRect(35, 262, 122, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(36, 263, 120, 38, 8, GREY);
    showmsg(50, 290, 1, GELO, &FreeSansBold12pt7b, "INICIAR");
    tft.drawRoundRect(175, 262, 117, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(176, 263, 115, 38, 8, GREY);
    showmsg(190, 290, 1, GELO, &FreeSansBold12pt7b, "PARAR");
    tft.drawRoundRect(310, 262, 132, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(311, 263, 130, 38, 8, TOMATO);
    showmsg(325, 290, 1, GELO, &FreeSansBold12pt7b, "VOLTAR");
    break;
  }
}

/* Telas para cada modo de operação */

void showTelaModoManual(int X, char *titulo)
{
  tft.fillScreen(KHAKI);                       //LIMPA A TELA
  tft.drawRoundRect(80, 5, 315, 45, 10, GREY); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(81, 6, 313, 43, 8, LGREEN);
  showmsgf(105 + X, 40, 1, BLACK, &FreeSansBold18pt7b, "MODO ", titulo);

  tft.drawRoundRect(20, 55, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 56, 273, 53, 8, GELO);
  showmsg(35, 90, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
  tft.drawRoundRect(305, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 56, 78, 53, 8, GELO);
  tft.drawRoundRect(385, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(386, 56, 78, 53, 8, GELO);

  tft.drawRoundRect(20, 125, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 126, 273, 53, 8, GELO);
  showmsg(98, 160, 1, BLACK, &FreeSansBold12pt7b, "DISTANCIA (m): ");
  tft.drawRoundRect(305, 125, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 126, 158, 53, 8, GELO);

  tft.drawRoundRect(20, 195, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 196, 273, 53, 8, GELO);
  showmsg(150, 230, 1, BLACK, &FreeSansBold12pt7b, "TEMPO (s): ");
  tft.drawRoundRect(305, 195, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);
}

void showTelaModoTCFM(int X, char *titulo)
{
  tft.fillScreen(KHAKI);                       //LIMPA A TELA
  tft.drawRoundRect(80, 5, 315, 45, 10, GREY); // (x, y, largura, altura, arredondamento)
  showmsgf(105 + X, 40, 1, BLACK, &FreeSansBold18pt7b, "MODO ", titulo);

  tft.drawRoundRect(20, 55, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 56, 273, 53, 8, GELO);
  showmsg(35, 90, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
  tft.drawRoundRect(305, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 56, 78, 53, 8, GELO);

  tft.drawRoundRect(20, 125, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 126, 273, 53, 8, GELO);
  showmsg(98, 160, 1, BLACK, &FreeSansBold12pt7b, "DISTANCIA (m): ");
  tft.drawRoundRect(305, 125, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 126, 158, 53, 8, GELO);

  tft.drawRoundRect(20, 195, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 196, 273, 53, 8, GELO);
  showmsg(150, 230, 1, BLACK, &FreeSansBold12pt7b, "TEMPO (s): ");
  tft.drawRoundRect(305, 195, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);
}

void showTelaModoTFA(int X, char *titulo)
{
  tft.fillScreen(KHAKI);                       //LIMPA A TELA
  tft.drawRoundRect(80, 5, 315, 45, 10, GREY); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(81, 6, 313, 43, 8, LGREEN);
  showmsgf(105 + X, 40, 1, BLACK, &FreeSansBold18pt7b, "MODO ", titulo);

  tft.drawRoundRect(20, 55, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 56, 273, 53, 8, GELO);
  showmsg(35, 90, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
  tft.drawRoundRect(305, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 56, 78, 53, 8, GELO);
  tft.drawRoundRect(385, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(386, 56, 78, 53, 8, GELO);

  tft.drawRoundRect(20, 125, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 126, 273, 53, 8, GELO);
  showmsg(98, 160, 1, BLACK, &FreeSansBold12pt7b, "DISTANCIA (m): ");
  tft.drawRoundRect(305, 125, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 126, 158, 53, 8, GELO);

  tft.drawRoundRect(20, 195, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(21, 196, 273, 53, 8, GELO);
  showmsg(150, 230, 1, BLACK, &FreeSansBold12pt7b, "TEMPO (s): ");
  tft.drawRoundRect(305, 195, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);
}

void ShowVelocidade()
{
  tft.drawRoundRect(305, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(306, 56, 78, 53, 8, GELO);
  Serial.println();
  Serial.print("Velocidade:");
  Serial.print(DadosEnsaio.velocidade);
  Serial.print("km/h");
}
void ShowTempoConfig(long TEMPOTOTAL)
{
  long seg1, seg2;
  long min1, min2;
  long hora1, hora2;
  static bool primeiravez = true;
  static long oldseg1 = 0, oldseg2 = 0;
  static long oldmin1 = 0, oldmin2 = 0;
  static long oldhora1 = 0, oldhora2 = 0;

  seg1 = ((TEMPOTOTAL % 60) % 10);
  seg2 = ((TEMPOTOTAL % 60) / 10);
  min1 = ((TEMPOTOTAL / 60) % 10);
  min2 = (((TEMPOTOTAL / 60) / 10) % 6);
  hora1 = ((TEMPOTOTAL / 3600) % 10);
  hora2 = ((TEMPOTOTAL / 3600) / 10);

  Serial.print(hora2);
  Serial.print(hora1);
  Serial.print(":");
  Serial.print(min2);
  Serial.print(min1);
  Serial.print(":");
  Serial.print(seg2);
  Serial.println(seg1);

  if (primeiravez)
  {
    showtempo(435, 235, 1, BLACK, &FreeSansBold18pt7b, seg1);
    showtempo(415, 235, 1, BLACK, &FreeSansBold18pt7b, seg2);
    showmsg(405, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(385, 235, 1, BLACK, &FreeSansBold18pt7b, min1);
    showtempo(365, 235, 1, BLACK, &FreeSansBold18pt7b, min2);
    showmsg(355, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(335, 235, 1, BLACK, &FreeSansBold18pt7b, hora1);
    showtempo(315, 235, 1, BLACK, &FreeSansBold18pt7b, hora2);

    oldseg1 = seg1;
    oldseg2 = seg2;
    oldmin1 = min1;
    oldmin2 = min2;
    oldhora1 = hora1;
    oldhora2 = hora2;
    primeiravez = false;
  }

  if (((min1 != oldmin1) || (min2 != oldmin2)) && (primeiravez == false))
  {
    // apaga os numeros anteriores somente se nao for a primeira vez
    showtempo(435, 235, 1, LGREEN, &FreeSansBold18pt7b, oldseg1);
    showtempo(415, 235, 1, LGREEN, &FreeSansBold18pt7b, oldseg2);
    showtempo(385, 235, 1, LGREEN, &FreeSansBold18pt7b, oldmin1);
    showtempo(365, 235, 1, LGREEN, &FreeSansBold18pt7b, oldmin2);
    showtempo(335, 235, 1, LGREEN, &FreeSansBold18pt7b, oldhora1);
    showtempo(315, 235, 1, LGREEN, &FreeSansBold18pt7b, oldhora2);
    //escreve os novos
    showtempo(435, 235, 1, BLACK, &FreeSansBold18pt7b, seg1);
    showtempo(415, 235, 1, BLACK, &FreeSansBold18pt7b, seg2);
    showmsg(405, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(385, 235, 1, BLACK, &FreeSansBold18pt7b, min1);
    showtempo(365, 235, 1, BLACK, &FreeSansBold18pt7b, min2);
    showmsg(355, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
    showtempo(335, 235, 1, BLACK, &FreeSansBold18pt7b, hora1);
    showtempo(315, 235, 1, BLACK, &FreeSansBold18pt7b, hora2);

    // atualiza
    oldseg1 = seg1;
    oldseg2 = seg2;
    oldmin1 = min1;
    oldmin2 = min2;
    oldhora1 = hora1;
    oldhora2 = hora2;
  }
}

void ShowTempoConfigOld(long TEMPOTOTAL)
{
  long seg1, seg2;
  long min1, min2;
  long hora1, hora2;
  static long oldseg1 = 0, oldseg2 = 0;
  static long oldmin1 = 0, oldmin2 = 0;
  static long oldhora1 = 0, oldhora2 = 0;

  seg1 = ((TEMPOTOTAL % 60) % 10);
  seg2 = ((TEMPOTOTAL % 60) / 10);
  min1 = ((TEMPOTOTAL / 60) % 10);
  min2 = (((TEMPOTOTAL / 60) / 10) % 6);
  hora1 = ((TEMPOTOTAL / 3600) % 10);
  hora2 = ((TEMPOTOTAL / 3600) / 10);

  // limpa a tela filling it
  tft.fillRoundRect(306, 196, 158, 53, 8, LGREEN);

  showtempo(435, 235, 1, BLACK, &FreeSansBold18pt7b, seg1);
  showtempo(415, 235, 1, BLACK, &FreeSansBold18pt7b, seg2);
  showmsg(405, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
  showtempo(385, 235, 1, BLACK, &FreeSansBold18pt7b, min1);
  showtempo(365, 235, 1, BLACK, &FreeSansBold18pt7b, min2);
  showmsg(355, 233, 1, BLACK, &FreeSansBold18pt7b, ":");
  showtempo(335, 235, 1, BLACK, &FreeSansBold18pt7b, hora1);
  showtempo(315, 235, 1, BLACK, &FreeSansBold18pt7b, hora2);

  // atualiza
  oldseg1 = seg1;
  oldseg2 = seg2;
  oldmin1 = min1;
  oldmin2 = min2;
  oldhora1 = hora1;
  oldhora2 = hora2;
}

void ShowTempoOld(long numinter)
{
  int seg1, seg2;
  int min1, min2;
  int hora1, hora2;
  static int oldseg1 = 0, oldseg2 = 0;
  static int oldmin1 = 0, oldmin2 = 0;
  static int oldhora1 = 0, oldhora2 = 0;

  seg1 = ((numinter % 60) % 10);
  seg2 = ((numinter % 60) / 10);
  min1 = ((numinter / 60) % 10);
  min2 = (((numinter / 60) / 10) % 6);
  hora1 = ((numinter / 3600) % 10);
  hora2 = ((numinter / 3600) / 10);

  // limpa a tela filling it
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);

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

void ShowTempo(long numinter)
{
  static bool primeiravez = true;
  int seg1, seg2;
  int min1, min2;
  int hora1, hora2;
  static int oldseg1 = 0, oldseg2 = 0;
  static int oldmin1 = 0, oldmin2 = 0;
  static int oldhora1 = 0, oldhora2 = 0;

  seg1 = ((numinter % 60) % 10);
  seg2 = ((numinter % 60) / 10);
  min1 = ((numinter / 60) % 10);
  min2 = (((numinter / 60) / 10) % 6);
  hora1 = ((numinter / 3600) % 10);
  hora2 = ((numinter / 3600) / 10);

  if (primeiravez == true)
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
    primeiravez = false;
  }

  if (((seg1 != oldseg1) || (seg2 != oldseg2)) && (primeiravez == false))
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

void showtempo(int x, int y, int sz, uint16_t color, const GFXfont *f, long t)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.printf("%ld", t);
}

void showmsg(int x, int y, int sz, uint16_t color, const GFXfont *f, const char *msg)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.print(msg);
}

void showmsgf(int x, int y, int sz, uint16_t color, const GFXfont *f, const char *txt, const char *msg)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.print(txt);
  tft.printf("%s", msg);
}

void showint(int x, int y, int sz, uint16_t color, const GFXfont *f, int t)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.printf("%d", t);
}

void showfloat(int x, int y, int sz, uint16_t color, const GFXfont *f, float t)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.printf("%.1f", t);
}

void showdist(int x, int y, int sz, uint16_t color, const GFXfont *f, float t)
{
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(sz);
  tft.printf("%.2f", t);
}

void showAbertura()
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
  showmsg(250, 310, 1, BLACK, &FreeSerifBold18pt7b, "UDESC/2020");
  showmsg(40, 240, 1, BLACK, &FreeSerifBold12pt7b, "Edwan Seiki Kuwakino");
  showmsg(40, 260, 1, BLACK, &FreeSerifBold12pt7b, "Leonardo Goncalves Rosa");
  showmsg(40, 280, 1, BLACK, &FreeSerifBold12pt7b, "Lucas Terres Hoffmann");
  showmsg(40, 300, 1, BLACK, &FreeSerifBold12pt7b, "Valdir Noll");
  delay(5000);
}
