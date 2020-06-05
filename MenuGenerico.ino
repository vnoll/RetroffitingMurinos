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
    tft.drawRoundRect(305, 55, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 56, 158, 53, 8, GELO);

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
    initTimer2();
    ShowTempo();
    primeiravez = 0;
  }
}
void pressionabotao()
{
	
  if (!digitalRead(ENTER))  pressbt = 1;
  if (digitalRead(ENTER) && pressbt)
  {
	Serial.println("pressionei botão");
    pressbt = 0;
    switch (pos)
    {
      case 1: 
        initTimer2();
        selecionado = 1;   // mostra o timer
        encoder.setPosition(2);
        break;

      case 2:
        selecionado = 0;//desliga o mostrador de timer
        encoder.setPosition(1);
        break;

      case 3:
        selecionado = 0; //desliga o timer
        primeiravez = 1; //flag que printa o menu uma única vez
        menu = 0; // executa o menu principal
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
    printabotao(newPos);
  }
}
void printabotao(int posicao)
{
  switch (posicao)
  {
    case 1:
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

    case 2:
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

    case 3:
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
