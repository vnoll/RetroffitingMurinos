void pressionabotaomanual()
{
  if (!digitalRead(ENTER))  BOTAOPRESSIONADO = ON;
  if (digitalRead(ENTER) && BOTAOPRESSIONADO)
  {
    BOTAOPRESSIONADO = OFF;
    if (BOTAOPRESSIONADO == OFF)
    {
      switch (pos)
      {
        case changevelocidade:
          SELECIONAVELOCIDADE = ON;
          primeiravez = ON;
          Y = 95;
          X = 402;
          tft.drawRoundRect(385, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
          tft.fillRoundRect(386, 56, 78, 53, 8, LGREEN);
          showVelocidadeDefinida(402, 95, velo);
          break;
        case iniciar:
          veloreal = 0;
          ZeraTimer();
          playtime = ON;   // mostra o timer
          encoder.setPosition(parar);//coloca o cursor sobre o botão parar
          break;

        case parar:
          playtime = OFF;//desliga o mostrador de timer
          break;

        case voltar:
          playtime = OFF; //desliga o mostrador de timer
          primeiravez = ON; //flag que printa o menu uma única vez
          menu = principal; // executa o menu principal
          break;
      }
    }
  }
}
void mudabotaomanual()
{
  encoder.tick();
  newPos = encoder.getPosition();
  if (pos != newPos)
  {
    //Limite maximo menu
    if (newPos > voltar)
    {
      encoder.setPosition(changevelocidade);
      newPos = changevelocidade;
    }
    //Limite minimo menu
    if (newPos < changevelocidade)
    {
      encoder.setPosition(voltar);
      newPos = voltar;
    }
    pos = newPos;
    printabotaomanual(newPos);
  }
}
void printabotaomanual(int posicao)
{
  switch (posicao)
  {
    case changevelocidade:
      tft.drawRoundRect(20, 55, 275, 55, 10, WHITE); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 56, 273, 53, 8, DBLUE);
      showmsg(35, 90, 1, GELO, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
      tft.drawRoundRect(35, 262, 122, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(36, 263, 120, 38, 8, GREY);
      showmsg(50, 290, 1, GELO, &FreeSansBold12pt7b, "INICIAR");
      tft.drawRoundRect(175, 262, 117, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(176, 263, 115, 38, 8, GREY);
      showmsg(190, 290, 1, GELO, &FreeSansBold12pt7b, "PARAR");
      tft.drawRoundRect(310, 262, 132, 40, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(311, 263, 130, 38, 8, GREY);
      showmsg(325, 290, 1, GELO, &FreeSansBold12pt7b, "VOLTAR");
      break;

    case iniciar:
      tft.drawRoundRect(20, 55, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 56, 273, 53, 8, GELO);
      showmsg(35, 90, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
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

    case parar:
      tft.drawRoundRect(20, 55, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 56, 273, 53, 8, GELO);
      showmsg(35, 90, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
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

    case voltar:
      tft.drawRoundRect(20, 55, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 56, 273, 53, 8, GELO);
      showmsg(35, 90, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
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
