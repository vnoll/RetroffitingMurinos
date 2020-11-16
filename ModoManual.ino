
int modoManual(int X, char *titulo)
{
    comando = PARAR;
    menu = MANUALL;  
    encoder.setPosition(1);
    pos = encoder.getPosition();
    showTelaModoManual(X, titulo);
    ShowOpcoesModoManual(); 
    
    DadosEnsaio.distanciaAcumulada = 0.0;
    DadosEnsaio.velocidade = 1.0;
	  DadosEnsaio.tempo = 0;
	  DadosEnsaio.config_velocidade = 1.0;
	  DadosEnsaio.config_tempo = 120; 

    ShowTempoConfig(DadosEnsaio.config_tempo);
    showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
    showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
    showDistancia(DadosEnsaio.distanciaAcumulada);
	
    do
    {       
      configVelocidade();   
      configTempo();
      ZeraTimer();
       
      comando==INICIAR;
      ShowOpcoesModoManual();   
      escolheComando();
      if (comando==VOLTAR) 
      {
        return 1;
      }
      // inicia o controle
      if (comando==INICIAR)
      {
		
        comando = PARAR;
        ShowOpcoesModoManual();
        DadosEnsaio.tempo =  DadosEnsaio.config_tempo;
        ZeraTimer();
		    // inicia controle em MF
        while (1)
        {
          updateVelocidadeEsteira();
          showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
          showDistancia(DadosEnsaio.distanciaAcumulada);          
          DadosEnsaio.tempo = DadosEnsaio.config_tempo - interruptCounter1s; 
          ShowTempo(DadosEnsaio.tempo);
          
          if (enterPressed || DadosEnsaio.tempo == 0){
            enterPressed = false; 
            break;
          }
        }
      }     
    }while (comando!=VOLTAR);
    enterPressed = false; 
}

void escolheComando()
{ 
  while (true)
  { 
   //Lê a posição do encoder e compara com a anterior
   encoder.tick();
   newPos  = encoder.getPosition();
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
      if (pos == 1) comando = INICIAR;
      else if (pos == 2) comando = PARAR;
      else comando = VOLTAR;
      ShowOpcoesModoManual();
    }
    if(enterPressed) break;
  }
  enterPressed = false;
}

void configVelocidade()
{
  float newvelo =DadosEnsaio.config_velocidade;
  static RotaryEncoder::Direction lastMovementDirection = RotaryEncoder::Direction::NOROTATION;
  //Lê a posição do encoder e compara com a anterior
  
  tft.drawRoundRect(385, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
  tft.fillRoundRect(386, 56, 78, 53, 8, LGREEN);
  showVelocidadeDefinida(402, 95,newvelo);  
  
  while (true)
  {  
    encoder.tick();
    RotaryEncoder::Direction currentDirection = encoder.getDirection();
    if (currentDirection == RotaryEncoder::Direction::CLOCKWISE)
    {
      newvelo = newvelo + 0.1;
      
      if (newvelo >= 5)
      {
        newvelo = 0;
      }
      showVelocidadeDefinida(402, 95, newvelo);
    }
    if (currentDirection == RotaryEncoder::Direction::COUNTERCLOCKWISE)
    {
      newvelo = newvelo - 0.1;
      if (newvelo < 0 || newvelo == -0.1)
      {
        newvelo = (5);
      }
      showVelocidadeDefinida(402, 95, newvelo);
    }
    if(enterPressed) break;
  }  
  DadosEnsaio.config_velocidade = newvelo;
  enterPressed = false;
}

void configTempo()
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
    if(enterPressed) break;
  }
  enterPressed = false;
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);  
  ShowTempoConfig(DadosEnsaio.config_tempo);  
}