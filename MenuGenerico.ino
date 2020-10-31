void menuGenerico()
{
  if (primeiravez)
  {
    tft.fillScreen(KHAKI);//LIMPA A TELA
    tft.drawRoundRect(80, 5, 315, 45, 10, GREY); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(81, 6, 313, 43, 8, LGREEN);
    showmsgf(105 + X, 40, 1, BLACK, &FreeSansBold18pt7b, "MODO ", modo);

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
    ZeraTimer();
    ShowTempo();
    primeiravez = ON;
    showVelocidadeReal(322, 95, veloreal);
    primeiravez = ON;
    showVelocidadeDefinida(402, 95, velo);
    primeiravez = ON;
    showDistancia();
    primeiravez = OFF;
  }
}
void pressionabotao()
{
	
  if (!digitalRead(ENTER))  BOTAOPRESSIONADO = ON;
  if (digitalRead(ENTER) && BOTAOPRESSIONADO)
  {
	Serial.println("pressionei botão");
    BOTAOPRESSIONADO = OFF;
    switch (pos)
    {
      case iniciar:
        veloreal =0;
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
void mudabotao()
{
  encoder.tick();
  newPos = encoder.getPosition();
  if (pos != newPos)
  {
    //Limite maximo menu
    if (newPos > voltar)
    {
      encoder.setPosition(iniciar);
      newPos = iniciar;
    }
    //Limite minimo menu
    if (newPos < iniciar)
    {
      encoder.setPosition(voltar);
      newPos = voltar;
    }
    pos = newPos;
    printabotao(newPos);
  }
}
void printabotao(int posicao)
{
  switch (posicao)
  {
    case iniciar:
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
