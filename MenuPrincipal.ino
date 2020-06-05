void menuPrincipal()
{
  if (primeiravez)
  {
    encoder.setPosition(4);
    tft.fillScreen(LBLUE);
    showmsg(188, 40, 1, BLACK, &FreeSansBold18pt7b, "MENU");
    primeiravez = 0;
  }
  //Lê a posição do encoder e compara com a anterior
  encoder.tick();
  newPos = encoder.getPosition();
  if (pos != newPos)
  {
    //Limite maximo menu
    if (newPos > 3)
    {
      encoder.setPosition(1);
      newPos = 1;
    }
    //Limite minimo menu
    if (newPos < 1)
    {
      encoder.setPosition(3);
      newPos = 3;
    }
    pos = newPos;
    printaopcoes(newPos);
  }
}
void printaopcoes(int posicao)
{
  switch (newPos)
  {
    case 1: //CURSOR EM MODO MANUAL
      tft.drawRoundRect(80, 70, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(81, 71, 318, 58, 8, DBLUE);
      showmsg(112, 110, 1, GELO, &FreeSansBold18pt7b, "Modo MANUAL");
      tft.drawFastHLine(112, 115, 258, GELO);

      tft.fillRoundRect(81, 151, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 150, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(140, 190, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");

      tft.fillRoundRect(81, 231, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 230, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(155, 270, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
      break;

    case 2://CURSOR EM MODO TCFM
      tft.drawRoundRect(80, 150, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(81, 151, 318, 58, 8, DBLUE);
      showmsg(140, 190, 1, GELO, &FreeSansBold18pt7b, "Modo TCFM");
      tft.drawFastHLine(140, 195, 205, GELO);

      tft.fillRoundRect(81, 71, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 70, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(112, 110, 1, BLACK, &FreeSansBold18pt7b, "Modo MANUAL");

      tft.fillRoundRect(81, 231, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 230, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(155, 270, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
      break;

    case 3://CURSOR EM MODO MANUAL TFA
      tft.drawRoundRect(80, 230, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(81, 231, 318, 58, 8, DBLUE);
      showmsg(155, 270, 1, GELO, &FreeSansBold18pt7b, "Modo TFA");
      tft.drawFastHLine(155, 275, 176, GELO);

      tft.fillRoundRect(81, 71, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 70, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(112, 110, 1, BLACK, &FreeSansBold18pt7b, "Modo MANUAL");

      tft.fillRoundRect(81, 151, 318, 58, 8, GELO);
      tft.drawRoundRect(80, 150, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      showmsg(140, 190, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");
      break;
  }
}
