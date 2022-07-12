
int modoTFA(int X, char *titulo)
{
  comando = PARAR;
  menu = TFAA;
  encoder.setPosition(3);
  pos = encoder.getPosition();
  showTelaModoTFA(X, titulo);
  ShowOpcoes();

  DadosEnsaio.distanciaAcumulada = 0.0;
  DadosEnsaio.velocidade = 0.0;
  DadosEnsaio.tempo = 0;
  DadosEnsaio.config_velocidade = 0.5;
  DadosEnsaio.config_tempo = 0;

  ShowTempoConfig(DadosEnsaio.config_tempo);
  showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
  showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
  showDistancia(DadosEnsaio.distanciaAcumulada);
  timerStop(timer);

  configVelocidadeTFA();
  configTempoTFA();

  // troca a cor para GELO e reescreve o mesmo valor configurado
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);
  ShowTempo(DadosEnsaio.config_tempo);
  showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
  showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
  ZeraTimer();
  do
  {
    ShowOpcoes();
    escolheComandoTFA();
    switch (comando)
    {
    case INICIAR:
      flagFuncionamento = true;
      flagOn = true;
      onOff();
      comando = PARAR;
      ShowOpcoes();
      timerRestart(timer);

      ShowTempo(DadosEnsaio.tempo);
      showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
      showDistancia(DadosEnsaio.distanciaAcumulada);

      // inicia controle em MF atualizando o valor do actualValueInterruptCounter1
      do
      {
        DadosEnsaio.tempo = DadosEnsaio.config_tempo - interruptCounter1s;
        if (DadosEnsaio.tempo <= 0)
          DadosEnsaio.tempo = 0;
        ShowTempo(DadosEnsaio.tempo);
        updateVelocidadeEsteira();
        showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
        showDistancia(DadosEnsaio.distanciaAcumulada);
      } while ((enterPressed == false && (DadosEnsaio.tempo > 0)));
      // fim do controle de MF

      timerStop(timer);
      enterPressed = false;
      DadosEnsaio.tempo = DadosEnsaio.config_tempo - interruptCounter1s;
      if (DadosEnsaio.tempo <= 0)
      {
        DadosEnsaio.tempo = 0;
        ShowTempo(DadosEnsaio.tempo);
        comando = VOLTAR;
        flagOn = false;
        onOff();
        ShowOpcoes();
        escolheComandoTFA();
        return 1;
      }
      ShowTempo(DadosEnsaio.tempo);
      comando = INICIAR;
      flagOn = false;
      onOff();
      break;

    case VOLTAR:
      flagFuncionamento = false;
      flagOn = false;
      onOff();
      pulsoAtivo = false;
      return 1;
      break;

    case PARAR:
      flagFuncionamento = false;
      flagOn = false;
      onOff();
      timerStop(timer);
      break;
    }
  } while (comando != VOLTAR);
  enterPressed = false;
}

void escolheComandoTFA()
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

void configVelocidadeTFA()
{
  float newvelo = DadosEnsaio.config_velocidade;
  static RotaryEncoder::Direction lastMovementDirection = RotaryEncoder::Direction::NOROTATION;
  //Lê a posição do encoder e compara com a anterior

  showVelocidadeDefinida(402, 95, newvelo);
  tft.drawRoundRect(385, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(386, 56, 78, 53, 8, LGREEN);
  showVelocidadeDefinida(402, 95, newvelo);

  while (true)
  {
    encoder.tick();
    RotaryEncoder::Direction currentDirection = encoder.getDirection();
    if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
    {
      newvelo = newvelo + 0.1;

      if (newvelo >= 5)
      {
        newvelo = 0.5;
      }
      showVelocidadeDefinida(402, 95, newvelo);
    }
    if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE)
    {
      newvelo = newvelo - 0.1;
      if (newvelo < 0.5 || newvelo == -0.1)
      {
        newvelo = (5);
      }
      showVelocidadeDefinida(402, 95, newvelo);
    }
    if (enterPressed)
      break;
  }
  DadosEnsaio.config_velocidade = newvelo;
  enterPressed = false;
}

void configTempoTFA()
{
  tft.fillRoundRect(306, 196, 158, 53, 8, LGREEN);
  ShowTempoConfig(DadosEnsaio.config_tempo);

  while (true)
  {
    //Lê a posição do encoder e compara com a anterior
    encoder.tick();
    RotaryEncoder::Direction currentDirection = encoder.getDirection();

    if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
    {
      DadosEnsaio.config_tempo = DadosEnsaio.config_tempo + 60;
      if (DadosEnsaio.config_tempo >= timermaximo)
      {
        DadosEnsaio.config_tempo = 0;
      }
      ShowTempoConfig(DadosEnsaio.config_tempo);
    }

    if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE)
    {
      DadosEnsaio.config_tempo = DadosEnsaio.config_tempo - 60;
      if (DadosEnsaio.config_tempo < 0)
      {
        DadosEnsaio.config_tempo = timermaximo;
      }
      ShowTempoConfig(DadosEnsaio.config_tempo);
    }
    if (enterPressed)
      break;
  }
  enterPressed = false;
}