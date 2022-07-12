
int modoTCFM(int X, char *titulo)
{
  comando = PARAR;
  menu = TCFM;
  encoder.setPosition(2);
  pos = encoder.getPosition();
  showTelaModoTCFM(X, titulo);
  ShowOpcoes();

  DadosEnsaio.distanciaAcumulada = 0.0;
  DadosEnsaio.velocidade = 0;
  DadosEnsaio.tempo = 0.0;
  DadosEnsaio.config_velocidade = 0.5;
  DadosEnsaio.config_tempo = 0.0;

  ZeraTimer();
  showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
  showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
  showDistancia(DadosEnsaio.distanciaAcumulada);
  timerStop(timer);

  // troca a cor para GELO e reescreve o mesmo valor configurado
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);
  ShowTempo(DadosEnsaio.config_tempo);

  ZeraTimer();
  do
  {
    ShowOpcoes();
    escolheComandoTCFM();
    switch (comando)
    {
    case INICIAR:
      flagFuncionamento = true;
      flagOn = true;
      comando = PARAR;
      ShowOpcoes();
      timerRestart(timer);

      // Início do controle de velocidade
      do
      {

        DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
        ShowTempo(DadosEnsaio.tempo);
        showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
        showDistancia(DadosEnsaio.distanciaAcumulada);
        updateVelocidadeEsteira();

        if (DadosEnsaio.tempo ==  300 || DadosEnsaio.tempo == 450  || DadosEnsaio.tempo == 600  || DadosEnsaio.tempo == 750  ||
            DadosEnsaio.tempo ==  900 || DadosEnsaio.tempo == 1050 || DadosEnsaio.tempo == 1200 || DadosEnsaio.tempo == 1350 ||
            DadosEnsaio.tempo == 1500 || DadosEnsaio.tempo == 1650 || DadosEnsaio.tempo == 1800 || DadosEnsaio.tempo == 1950 ||
            DadosEnsaio.tempo == 2100 || DadosEnsaio.tempo == 2250 || DadosEnsaio.tempo == 2400 || DadosEnsaio.tempo == 2550 ||
            DadosEnsaio.tempo == 2700 || DadosEnsaio.tempo == 2850 || DadosEnsaio.tempo == 3000 || DadosEnsaio.tempo == 3150 ||
            DadosEnsaio.tempo == 3300 || DadosEnsaio.tempo == 3450 || DadosEnsaio.tempo == 3600 || DadosEnsaio.tempo == 3750 ||
            DadosEnsaio.tempo == 3900 || DadosEnsaio.tempo == 4050 || DadosEnsaio.tempo == 4200 || DadosEnsaio.tempo == 4350 ||
            DadosEnsaio.tempo == 4500 || DadosEnsaio.tempo == 4650 || DadosEnsaio.tempo == 4800 || DadosEnsaio.tempo == 4950 ||
            DadosEnsaio.tempo == 5100 || DadosEnsaio.tempo == 5250 || DadosEnsaio.tempo == 5400 || DadosEnsaio.tempo == 5550 ||
            DadosEnsaio.tempo == 5700 || DadosEnsaio.tempo == 5850 || DadosEnsaio.tempo == 6000 || DadosEnsaio.tempo == 6150 ||
            DadosEnsaio.tempo == 6300 || DadosEnsaio.tempo == 6450 || DadosEnsaio.tempo == 6600 || DadosEnsaio.tempo == 6750 ||
            DadosEnsaio.tempo == 6900)

        {
          DadosEnsaio.config_velocidade += 0.1;
          DadosEnsaio.velocidade = DadosEnsaio.config_velocidade;
          updateVelocidadeEsteira();
          ShowVelocidade();
          DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
          ShowTempo(DadosEnsaio.tempo);
          showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
          showDistancia(DadosEnsaio.distanciaAcumulada);
        }

      } while ((enterPressed == false && (DadosEnsaio.velocidade <= 5)));
      // Fim do controle de MF

      timerStop(timer);
      enterPressed = false;
      DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
      if (DadosEnsaio.tempo <= 10000)
      {
        ShowTempo(DadosEnsaio.tempo);
        comando = VOLTAR;
        ShowOpcoes();
        escolheComandoTCFM();
        return 1;
      }
      ShowTempo(DadosEnsaio.tempo);
      comando = INICIAR;
      break;

    case VOLTAR:
      flagFuncionamento = false;
      flagOn = false;
      return 1;
      break;

    case PARAR:
      flagFuncionamento = false;
      flagOn = false;
      timerStop(timer);
      break;
    }
  } while (comando != VOLTAR);
  enterPressed = false;
}

void escolheComandoTCFM()
{
  while (true)
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
      if (pos == 1)
        comando = INICIAR;
      else if (pos == 2)
        comando = PARAR;
      else
        comando = VOLTAR;
      ShowOpcoes();
    }
    if (enterPressed)
      break;
  }
  enterPressed = false;
}
