// TFA = Treinamento Fisico Aerobio
int menuTFA()
{
  if (primeiravez)
  {
    tft.fillScreen(KHAKI);
    showmsg(70, 50, 1, BLACK, &FreeSerifBold24pt7b, "Configurar TFA");
    tft.drawRoundRect(305, 105, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 106, 158, 53, 8, GELO);
    tft.drawRoundRect(305, 175, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 176, 158, 53, 8, GELO);
    showVelocidade(0);
    ShowTempoTFA(0);
    primeiravez = 0;
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
    printabotaotfa(newPos);
  }
}
void mudavelocidade()
{
  //Lê a posição do encoder e compara com a anterior
  encoder.tick();
  newvelo = encoder.getPosition();
  if (velo != newvelo)
  {
    //Limite maximo menu
    if (newvelo > 50)
    {
      encoder.setPosition(1);
      newvelo = 1;
    }
    //Limite minimo menu
    if (newvelo < 1)
    {
      encoder.setPosition(50);
      newvelo = 50;
    }
    velo = newvelo;
    showVelocidade(velo);
  }
}
void mudatempo()
{
  //Lê a posição do encoder e compara com a anterior
  encoder.tick();
  NEWTEMPOTOTAL = encoder.getPosition();
  if (TEMPOTOTAL != NEWTEMPOTOTAL)
  {
    if (TEMPOTOTAL < NEWTEMPOTOTAL)
    {
      TEMPOTOTAL = (TEMPOTOTAL + 60);
    }
    if (TEMPOTOTAL > NEWTEMPOTOTAL)
    {
      TEMPOTOTAL = (TEMPOTOTAL - 60);
    }
    //Limite maximo menu
    if (NEWTEMPOTOTAL > 8640)
    {
      encoder.setPosition(1);
      NEWTEMPOTOTAL = 1;
    }
    //Limite minimo menu
    if (NEWTEMPOTOTAL < 1)
    {
      encoder.setPosition(8640);
      NEWTEMPOTOTAL = 8640;
    }
    TEMPOTOTAL = NEWTEMPOTOTAL;
    ShowTempoTFA(TEMPOTOTAL);
  }
}
void pressionatfa()
{
  //LÊ SE O BOTÃO FOI PRESSIONADO E LEVANTA A FLAG
  if (!digitalRead(ENTER)) pressbt = 0x01;
  if (digitalRead(ENTER) && pressbt)
  {
    pressbt = 0x00; //ABAIXA A FLAG DO BOTÃO
    switch (pos)
    {
      case changevelocidade:
        selecionado = 1;
        primeiravez = 1;
        tft.drawRoundRect(305, 105, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
        tft.fillRoundRect(306, 106, 158, 53, 8, LGREEN);
        encoder.setPosition(velo);
        showVelocidade(velo);
        while (selecionado)
        {
          mudavelocidade();
          //LÊ SE O BOTÃO FOI PRESSIONADO E LEVANTA A FLAG
          if (!digitalRead(ENTER)) pressbt = 0x01;
          if (digitalRead(ENTER) && pressbt)
          {
            pressbt = 0x00; //ABAIXA A FLAG DO BOTÃO
            primeiravez = 1;
            tft.drawRoundRect(305, 105, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
            tft.fillRoundRect(306, 106, 158, 53, 8, GELO);
            showVelocidade(velo);
            selecionado = 0;
            encoder.setPosition(1);
          }
        }
        break;
      case changetempo:
        selecionado = 1;
        primeiravez = 1;
        tft.drawRoundRect(305, 175, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
        tft.fillRoundRect(306, 176, 158, 53, 8, LGREEN);
        encoder.setPosition(TEMPOTOTAL);
        ShowTempoTFA(TEMPOTOTAL);
        while (selecionado)
        {
          mudatempo();
          //LÊ SE O BOTÃO FOI PRESSIONADO E LEVANTA A FLAG
          if (!digitalRead(ENTER)) pressbt = 0x01;
          if (digitalRead(ENTER) && pressbt)
          {
            pressbt = 0x00; //ABAIXA A FLAG DO BOTÃO
            primeiravez = 1;
            tft.drawRoundRect(305, 175, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
            tft.fillRoundRect(306, 176, 158, 53, 8, GELO);
            ShowTempoTFA(TEMPOTOTAL);
            selecionado = 0;
            encoder.setPosition(2);
          }
        }
        break;
      case confirma://SE FOI DADO UM ENTER NA TERCEIRA POSIÇÃO VAI PARA O MENU GENÉRICO
        primeiravez = 1;//FLAG DA PRIMEIRA VEZ NO MENU
        encoder.setPosition(4);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO DO MENU GENÉRICO
        menu = tfagenerico;
        menuGenerico();
        break;
    }
  }
}
void printabotaotfa(int posicao)
{
  switch (posicao)
  {
    case 1://CURSOR EM VELOCIDADE
      tft.drawRoundRect(20, 105, 275, 55, 10, GELO); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 106, 273, 53, 8, DBLUE);
      showmsg(35, 140, 1, GELO, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");

      tft.drawRoundRect(20, 175, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 176, 273, 53, 8, GELO);
      showmsg(70, 210, 1, BLACK, &FreeSansBold12pt7b, "TEMPO TOTAL(s): ");

      tft.drawRoundRect(305, 245, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(306, 246, 158, 53, 8, GREY);
      showmsg(319, 280, 1, GELO, &FreeSansBold12pt7b, "CONFIRMA");
      break;
    case 2://CURSOR EM TEMPO TOTAL
      tft.drawRoundRect(20, 105, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 106, 273, 53, 8, GELO);
      showmsg(35, 140, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");

      tft.drawRoundRect(20, 175, 275, 55, 10, GELO); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 176, 273, 53, 8, DBLUE);
      showmsg(70, 210, 1, GELO, &FreeSansBold12pt7b, "TEMPO TOTAL(s): ");

      tft.drawRoundRect(305, 245, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(306, 246, 158, 53, 8, GREY);
      showmsg(319, 280, 1, GELO, &FreeSansBold12pt7b, "CONFIRMA");
      break;
    case 3://CURSOR EM ENTER
      tft.drawRoundRect(20, 105, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 106, 273, 53, 8, GELO);
      showmsg(35, 140, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");

      tft.drawRoundRect(20, 175, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(21, 176, 273, 53, 8, GELO);
      showmsg(70, 210, 1, BLACK, &FreeSansBold12pt7b, "TEMPO TOTAL(s): ");

      tft.drawRoundRect(305, 245, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
      tft.fillRoundRect(306, 246, 158, 53, 8, TOMATO);
      showmsg(319, 280, 1, GELO, &FreeSansBold12pt7b, "CONFIRMA");
      break;
  }
}
