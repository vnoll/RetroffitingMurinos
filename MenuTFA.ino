// TFA = Treinamento Fisico Aerobio
int menuTFA()
{
  if (primeiravez)
  {
    tft.fillScreen(KHAKI);
    tft.drawRoundRect(55, 15, 365, 60, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(56, 16, 363, 58, 8, LGREEN);
    showmsg(70, 60, 1, BLACK, &FreeSerifBold24pt7b, "Configurar TFA");
    tft.drawRoundRect(305, 105, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 106, 158, 53, 8, GELO);
    tft.drawRoundRect(305, 175, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 176, 158, 53, 8, GELO);
    showVelocidadeDefinida(362,145, 0);
    primeiravez = ON;
    ShowTempoTFA();
    primeiravez = ON;
    primeiravez = OFF;
  }
}
void mudatfa()
{
  //Lê a posição do encoder e compara com a anterior
  encoder.tick();
  newPos = encoder.getPosition();
  if (pos != newPos)
  {
    //Limite maximo menu
    if (newPos > confirma)
    {
      encoder.setPosition(changevelocidade);
      newPos = changevelocidade;
    }
    //Limite minimo menu
    if (newPos < changevelocidade)
    {
      encoder.setPosition(confirma);
      newPos = confirma;
    }
    pos = newPos;
    printabotaotfa(newPos);
  }
}
void mudavelocidade()
{
  static RotaryEncoder::Direction lastMovementDirection = RotaryEncoder::Direction::NOROTATION;
  //Lê a posição do encoder e compara com a anterior
  encoder.tick();
  NEWTEMPOTOTAL = TEMPOTOTAL;
  RotaryEncoder::Direction currentDirection = encoder.getDirection();
  if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
  {
    newvelo = velo + 0.1;
    if (newvelo >= 5)
    {
      newvelo = 0;
    }
    if (velo != newvelo)
    {
      velo = newvelo;
      Serial.println(velo);
      showVelocidadeDefinida(X, Y, velo);
    }
  }
  if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE)
  {
    newvelo = velo - 0.1;
    if (newvelo < 0 || newvelo == -0.1)
    {
      newvelo = (5);
    }
    if (velo != newvelo)
    {
      velo = newvelo;
      showVelocidadeDefinida(X, Y, velo);
    }
  }
}
void mudatempo()
{
  static RotaryEncoder::Direction lastMovementDirection = RotaryEncoder::Direction::NOROTATION;
  //Lê a posição do encoder e compara com a anterior
  encoder.tick();
  NEWTEMPOTOTAL = TEMPOTOTAL;
  RotaryEncoder::Direction currentDirection = encoder.getDirection();
  if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
  {
    NEWTEMPOTOTAL = TEMPOTOTAL + 60;
    if (NEWTEMPOTOTAL >= timermaximo)
    {
      NEWTEMPOTOTAL = 0;
      Serial.println(TEMPOTOTAL);
    }
    if (TEMPOTOTAL != NEWTEMPOTOTAL)
    {
      TEMPOTOTAL = NEWTEMPOTOTAL;
      ShowTempoTFA();
    }
  }
  if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE)
  {
    NEWTEMPOTOTAL = TEMPOTOTAL - 60;
    if (NEWTEMPOTOTAL < 0 || NEWTEMPOTOTAL == -60)
    {
      NEWTEMPOTOTAL = (timermaximo - 60);
    }
    if (TEMPOTOTAL != NEWTEMPOTOTAL)
    {
      TEMPOTOTAL = NEWTEMPOTOTAL;
      ShowTempoTFA();
    }
  }
}
void pressionatfa()
{
  //LÊ SE O BOTÃO FOI PRESSIONADO E LEVANTA A FLAG
  if (!digitalRead(ENTER)) BOTAOPRESSIONADO = ON;
  if (digitalRead(ENTER) && BOTAOPRESSIONADO)
  {
    BOTAOPRESSIONADO = OFF; //ABAIXA A FLAG DO BOTÃO
    switch (pos)
    {
      case changevelocidade:
        selecionado = ON;
        primeiravez = ON;
        tft.drawRoundRect(305, 105, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
        tft.fillRoundRect(306, 106, 158, 53, 8, LGREEN);
        Y = 145;
        X = 362;
        encoder.setPosition(velo);
        showVelocidadeDefinida(X, Y, velo);
        while (selecionado)
        {
          mudavelocidade();
          //LÊ SE O BOTÃO FOI PRESSIONADO E LEVANTA A FLAG
          if (!digitalRead(ENTER)) BOTAOPRESSIONADO = ON;
          if (digitalRead(ENTER) && BOTAOPRESSIONADO)
          {
            BOTAOPRESSIONADO = OFF; //ABAIXA A FLAG DO BOTÃO
            primeiravez = ON;
            tft.drawRoundRect(305, 105, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
            tft.fillRoundRect(306, 106, 158, 53, 8, GELO);
            showVelocidadeDefinida(X, Y, velo);
            selecionado = OFF;
            encoder.setPosition(changevelocidade);
          }
        }
        break;
      case changetempo:
        selecionado = ON;
        primeiravez = ON;
        tft.drawRoundRect(305, 175, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
        tft.fillRoundRect(306, 176, 158, 53, 8, LGREEN);
        encoder.setPosition(TEMPOTOTAL);
        ShowTempoTFA();
        while (selecionado)
        {
          mudatempo();
          //LÊ SE O BOTÃO FOI PRESSIONADO E LEVANTA A FLAG
          if (!digitalRead(ENTER)) BOTAOPRESSIONADO = ON;
          if (digitalRead(ENTER) && BOTAOPRESSIONADO)
          {
            BOTAOPRESSIONADO = OFF; //ABAIXA A FLAG DO BOTÃO
            primeiravez = ON;
            tft.drawRoundRect(305, 175, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
            tft.fillRoundRect(306, 176, 158, 53, 8, GELO);
            ShowTempoTFA();
            selecionado = OFF;
            encoder.setPosition(2);
          }
        }
        break;
      case confirma://SE FOI DADO UM ENTER NA TERCEIRA POSIÇÃO VAI PARA O MENU GENÉRICO
        primeiravez = ON;//FLAG DA PRIMEIRA VEZ NO MENU
        encoder.setPosition(4);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO DO MENU GENÉRICO
        menu = tfagenerico;
        X = 40;//Ajusta a posição do título
        menuGenerico();
        break;
    }
  }
}
void printabotaotfa(int posicao)
{
  switch (posicao)
  {
    case changevelocidade://CURSOR EM VELOCIDADE
      tft.drawRoundRect(20, 105, 275, 55, 10, GELO); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 106, 273, 53, 8, DBLUE);
      showmsg(35, 140, 1, GELO, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");

      tft.drawRoundRect(20, 175, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 176, 273, 53, 8, GELO);
      showmsg(100, 210, 1, BLACK, &FreeSansBold12pt7b, "TEMPO TOTAL:");

      tft.drawRoundRect(305, 245, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(306, 246, 158, 53, 8, GREY);
      showmsg(319, 280, 1, GELO, &FreeSansBold12pt7b, "CONFIRMA");
      break;
    case changetempo://CURSOR EM TEMPO TOTAL
      tft.drawRoundRect(20, 105, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 106, 273, 53, 8, GELO);
      showmsg(35, 140, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");

      tft.drawRoundRect(20, 175, 275, 55, 10, GELO); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 176, 273, 53, 8, DBLUE);
      showmsg(100, 210, 1, GELO, &FreeSansBold12pt7b, "TEMPO TOTAL:");

      tft.drawRoundRect(305, 245, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(306, 246, 158, 53, 8, GREY);
      showmsg(319, 280, 1, GELO, &FreeSansBold12pt7b, "CONFIRMA");
      break;
    case confirma://CURSOR EM ENTER
      tft.drawRoundRect(20, 105, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 106, 273, 53, 8, GELO);
      showmsg(35, 140, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");

      tft.drawRoundRect(20, 175, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 176, 273, 53, 8, GELO);
      showmsg(100, 210, 1, BLACK, &FreeSansBold12pt7b, "TEMPO TOTAL: ");

      tft.drawRoundRect(305, 245, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(306, 246, 158, 53, 8, TOMATO);
      showmsg(319, 280, 1, GELO, &FreeSansBold12pt7b, "CONFIRMA");
      break;
  }
}
