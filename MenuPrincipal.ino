void menuPrincipal()
{
  if (primeiravez)
  {
    encoder.setPosition(manual);//reseta o cursor
    tft.fillScreen(LBLUE);//limpa a tela
    tft.drawRoundRect(143, 11, 200, 50, 6, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(144, 12, 198, 48, 4, DORANGE);
    showmsg(163, 50, 2, BLACK, &FreeSansBold12pt7b, "M");
    showmsg(207, 50, 2, BLACK, &FreeSansBold12pt7b, "E");
    showmsg(243, 50, 2, BLACK, &FreeSansBold12pt7b, "N");
    showmsg(283, 50, 2, BLACK, &FreeSansBold12pt7b, "U");
    showmsg(167, 51, 1, GELO, &FreeSansBold24pt7b, "M");
    showmsg(212, 51, 1, GELO, &FreeSansBold24pt7b, "E");
    showmsg(248, 51, 1, GELO, &FreeSansBold24pt7b, "N");
    showmsg(288, 51, 1, GELO, &FreeSansBold24pt7b, "U");
    primeiravez = OFF;
  }
}
void mudaopcoes()
{
  //Lê a posição do encoder e compara com a anterior
  encoder.tick();
  newPos = encoder.getPosition();
  if (pos != newPos)
  {
    //Limite maximo menu
    if (newPos > tfa)
    {
      encoder.setPosition(manual);
      newPos = manual;
    }
    //Limite minimo menu
    if (newPos < manual)
    {
      encoder.setPosition(tfa);
      newPos = tfa;
    }
    pos = newPos;
    printaopcoes(newPos);
  }
}
void printaopcoes(int posicao)
{
  switch (newPos)
  {
    case manual: //CURSOR EM MODO MANUAL
      tft.drawRoundRect(80, 80, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(81, 81, 318, 58, 8, DBLUE);
      showmsg(112, 120, 1, GELO, &FreeSansBold18pt7b, "Modo MANUAL");
      tft.drawFastHLine(112, 125, 258, GELO);

      tft.fillRoundRect(81, 161, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 160, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(140, 200, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");

      tft.fillRoundRect(81, 241, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 240, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(155, 280, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
      break;

    case tcfm://CURSOR EM MODO TCFM
      tft.drawRoundRect(80, 160, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(81, 161, 318, 58, 8, DBLUE);
      showmsg(140, 200, 1, GELO, &FreeSansBold18pt7b, "Modo TCFM");
      tft.drawFastHLine(140, 205, 205, GELO);

      tft.fillRoundRect(81, 81, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 80, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(112, 120, 1, BLACK, &FreeSansBold18pt7b, "Modo MANUAL");

      tft.fillRoundRect(81, 241, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 240, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(155, 280, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
      break;

    case tfa://CURSOR EM MODO MANUAL TFA
      tft.drawRoundRect(80, 240, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(81, 241, 318, 58, 8, DBLUE);
      showmsg(155, 280, 1, GELO, &FreeSansBold18pt7b, "Modo TFA");
      tft.drawFastHLine(155, 285, 176, GELO);

      tft.fillRoundRect(81, 81, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 80, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(112, 120, 1, BLACK, &FreeSansBold18pt7b, "Modo MANUAL");

      tft.fillRoundRect(81, 161, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 160, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(140, 200, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");
      break;
  }
}
