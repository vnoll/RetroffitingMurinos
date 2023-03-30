

void menuPrincipal()
{
  comando = PARAR;
  menu = MANUALL;
  encoder.setPosition(menu);
  pos = encoder.getPosition();
  desenhaTitulo();
  escolheOpcao();
}

void desenhaTitulo()
{
  tft.fillScreen(LBLUE);                                         // limpa a tela
  tft.drawRoundRect(143, 11, 200, 50, 6, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(144, 12, 198, 48, 4, LGREEN);

  showmsg(163, 50, 2, BLACK, &FreeSansBold12pt7b, "M");
  showmsg(207, 50, 2, BLACK, &FreeSansBold12pt7b, "E");
  showmsg(243, 50, 2, BLACK, &FreeSansBold12pt7b, "N");
  showmsg(283, 50, 2, BLACK, &FreeSansBold12pt7b, "U");

  //showmsg(167, 51, 1, GELO, &FreeSansBold24pt7b, "M");
  //showmsg(212, 51, 1, GELO, &FreeSansBold24pt7b, "E");
  //showmsg(248, 51, 1, GELO, &FreeSansBold24pt7b, "N");
  //showmsg(288, 51, 1, GELO, &FreeSansBold24pt7b, "U");
  imprimeMenu();
}

void imprimeMenu()
{
  switch (menu)
  {
  case MANUALL:                                    // CURSOR EM MODO MANUAL
    tft.drawRoundRect(80, 80, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(81, 81, 318, 58, 8, DBLUE);
    showmsg(112, 120, 1, GELO, &FreeSansBold18pt7b, "Modo MANUAL");
    tft.drawFastHLine(112, 125, 258, GELO);

    tft.fillRoundRect(81, 161, 318, 58, 8, GELO);
    tft.drawRoundRect(80, 160, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    //showmsg(140, 200, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");
    showmsg(112, 200, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");
    tft.fillRoundRect(81, 241, 318, 58, 8, GELO);
    tft.drawRoundRect(80, 240, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    //showmsg(155, 280, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
    showmsg(112, 280, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
    break;

  case TCFM:                                        // CURSOR EM MODO TCFM
    tft.drawRoundRect(80, 160, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(81, 161, 318, 58, 8, DBLUE);
    //showmsg(140, 200, 1, GELO, &FreeSansBold18pt7b, "Modo TCFM");
    showmsg(112, 200, 1, GELO, &FreeSansBold18pt7b, "Modo TCFM");
    //tft.drawFastHLine(140, 205, 205, GELO);
    tft.drawFastHLine(112, 205, 205, GELO);

    tft.fillRoundRect(81, 81, 318, 58, 8, GELO);
    tft.drawRoundRect(80, 80, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    showmsg(112, 120, 1, BLACK, &FreeSansBold18pt7b, "Modo MANUAL");

    tft.fillRoundRect(81, 241, 318, 58, 8, GELO);
    tft.drawRoundRect(80, 240, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    //showmsg(155, 280, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
    showmsg(112, 280, 1, BLACK, &FreeSansBold18pt7b, "Modo TFA");
    break;

  case TFAA:                                        // CURSOR EM MODO MANUAL TFA
    tft.drawRoundRect(80, 240, 320, 60, 10, WHITE); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(81, 241, 318, 58, 8, DBLUE);
    //showmsg(155, 280, 1, GELO, &FreeSansBold18pt7b, "Modo TFA");
    showmsg(112, 280, 1, GELO, &FreeSansBold18pt7b, "Modo TFA");
    //tft.drawFastHLine(155, 285, 176, GELO);
    tft.drawFastHLine(112, 285, 176, GELO);

    tft.fillRoundRect(81, 81, 318, 58, 8, GELO);
    tft.drawRoundRect(80, 80, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    showmsg(112, 120, 1, BLACK, &FreeSansBold18pt7b, "Modo MANUAL");

    tft.fillRoundRect(81, 161, 318, 58, 8, GELO);
    tft.drawRoundRect(80, 160, 320, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    //showmsg(140, 200, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");
    showmsg(112, 200, 1, BLACK, &FreeSansBold18pt7b, "Modo TCFM");
    break;
  }
}

void escolheOpcao()
{
  unsigned char pos_atual_encoder = 0;
  while (true)
  {
    // Lê a posição do encoder e compara com a anterior
    encoder.tick();
    newPos = encoder.getPosition();

    if (pos != newPos)
    {
      // Limite maximo menu
      if (newPos > 3)
      {
        encoder.setPosition(1);
        newPos = 1;
      }
      // Limite minimo menu
      if (newPos < 1)
      {
        encoder.setPosition(3);
        newPos = 3;
      }
      pos = newPos;
      if (pos == 1)
        menu = MANUALL;
      else if (pos == 2)
        menu = TCFM;
      else
        menu = TFAA;
      imprimeMenu();
    }
    if (enterPressed)
      break;
  }
  enterPressed = false;
}
