int modoManual(int X, char *titulo)
{
  comando = INICIAR;
  menu = MANUALL;
  encoder.setPosition(1);
  pos = encoder.getPosition();
  showTelaModoManual(X, titulo);
  ShowOpcoes();

  DadosEnsaio.distanciaAcumulada = 0.0;
  DadosEnsaio.velocidade = 0;
  DadosEnsaio.tempo = 0;
  DadosEnsaio.config_velocidade = 0.5;

  showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
  tft.fillRoundRect(386, 56, 78, 53, 8, LGREEN);
  showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
  showDistancia(DadosEnsaio.distanciaAcumulada);
  timerStop(timer);
  ZeraTimer();
  ShowTempo(DadosEnsaio.tempo);

  do
  {
    escolheComandoManual();
    switch (comando)
    {
    case INICIAR:
      flagFuncionamento = true;
      flagOn = true;
      onOff();
      comando = PARAR;
      ShowOpcoes();
      timerRestart(timer);

      // Inicialização do controle da esteira
      do
      {
        DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
        ShowTempo(DadosEnsaio.tempo);
        showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
        showDistancia(DadosEnsaio.distanciaAcumulada);

        showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
        updateVelocidadeEsteira();
        
        encoder.tick();
        newPos = encoder.getPosition();
        if (pos != newPos)
        {
          configVelocidade();
          //showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
        }      

      } while ((enterPressed == false && comando != VOLTAR));

      // Fim do controle
      flagOn = false;
      onOff();
      timerStop(timer);
      enterPressed = false;
      DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
      ShowTempo(DadosEnsaio.tempo);
      comando = INICIAR;
      ZeraTimer();
      break;

    case VOLTAR:
      flagFuncionamento = false;
      flagOn = false;
      onOff();
      ZeraTimer();
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

void escolheComandoManual()
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

void configVelocidade()
{
  static int primeiravez =0;
  float newvelo = DadosEnsaio.config_velocidade;
  static RotaryEncoder::Direction lastMovementDirection = RotaryEncoder::Direction::NOROTATION;
  //Lê a posição do encoder e compara com a anterior

  if (primeiravez == 0) {
    tft.drawRoundRect(385, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(386, 56, 78, 53, 8, LGREEN);
    showVelocidadeDefinida(402, 95, newvelo);
    primeiravez = 1;
  }
  encoder.tick();
  RotaryEncoder::Direction currentDirection = encoder.getDirection();
  if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
    {
      newvelo = newvelo + 0.1;

      if (newvelo >= 5)
      {
        newvelo = 0.5;
      }
      //showVelocidadeDefinida(402, 95, newvelo);
    }
  if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE)
    {
      newvelo = newvelo - 0.1;
      if (newvelo < 0.5 || newvelo == -0.1)
      {
        newvelo = (5);
      }
      //showVelocidadeDefinida(402, 95, newvelo);
    }
  DadosEnsaio.config_velocidade = newvelo;
  showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade); 
}
