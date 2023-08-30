
int modoTCFM(int X, char *titulo)
{
  // valor real
  long valorControle[45] = {300,450,600,750,900,1050,1200,1350,1500,1650,1800,1950,2100,2250,2400,2550,2700,
                          2850,3000,3150,3300,3450,3600,3750,3900,4050,4200,4350,4500,4650,4800,4950,5100,
                          5250,5400,5550,5700,5850,6000,6150,6300,6450,6600,6750,6900};

  // para testes 10x menos velocidade
  //long valorControle[45] = {30,45,60,75,90,105,120,135,150,165,180,195,210,225,240,255,270,
  //                        285,300,315,330,345,360,375,390,405,420,435,450,465,480,495,510,
  //                       525,540,555,570,585,600,615,630,645,660,675,690};

  int flag_entrou = 1;
  long tempoEnsaio = 0;
  long tempoEnsaioAnterior = 0;
  int idx = 0;
  
  comando = PARAR;
  menu = TCFM;
  encoder.setPosition(2);
  pos = encoder.getPosition();
  showTelaModoTCFM(X, titulo);
  ShowOpcoes();

  DadosEnsaio.distanciaAcumulada = 0.0;
  DadosEnsaio.velocidade = 0.0;
  DadosEnsaio.tempo = 0;
  DadosEnsaio.config_velocidade = 0.5;
  DadosEnsaio.config_tempo = 0;

  primeiravez_showDistancia = true; //Flag primeiravez
  primeiravez_showVelocidadeReal = true;
  primeiravez_showVelocidadeDefinida = true;
  primeiravez_ShowTempoConfig = true;
  primeiravez_ShowTempo = true;

  ZeraTimer();
  showVelocidadeReal(322, 95, DadosEnsaio.velocidade);

  tft.fillRoundRect(386, 56, 78, 53, 8, LGREEN);
  showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
  showDistancia(DadosEnsaio.distanciaAcumulada);
  timerStop(timer);

  // troca a cor para GELO e reescreve o mesmo valor configurado
  tft.fillRoundRect(306, 196, 158, 53, 8, GELO);
  ShowTempo(DadosEnsaio.config_tempo);

  ZeraTimer();
  unsigned long periodoControle = 0;
  unsigned long periodoToShow = 0;
  Serial.println("Tempo(s), Velocidade Definida(km/h),Velocidade Real (km/h),Distancia percorrida (m)");
 
  do
  {
    ShowOpcoes();
    escolheComandoTCFM();
    switch (comando)
    {
    case INICIAR:
      flagFuncionamento = true;
      flagOn = true;
      onOff();
      comando = PARAR;
      ShowOpcoes();
      timerRestart(timer);
      periodoToShow = millis();
      periodoControle = millis();
      

      // Início do controle de velocidade
      do
      {
        DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
        
        if ((millis()-periodoControle)>50)
        {
          updateVelocidadeEsteira();
          periodoControle = millis();
        }
        if ((millis()-periodoToShow)>300)
            {
              ShowTempo(DadosEnsaio.tempo);
              showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
              showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
              showDistancia(DadosEnsaio.distanciaAcumulada);
              periodoToShow = millis();
              PrintDataSERIAL4Debug();
            }
        tempoEnsaio = DadosEnsaio.tempo;
         
        if (flag_entrou == 0)
        {
          if (tempoEnsaio != tempoEnsaioAnterior) flag_entrou = 1;
        }

        if ((tempoEnsaio >= valorControle[idx]) && (flag_entrou == 1))
        {
          flag_entrou = 0;
          idx++;
          if (idx >= 45) {
            idx = 0;
            break;
          }
          tempoEnsaioAnterior = tempoEnsaio;
          DadosEnsaio.config_velocidade += 0.1;

          //DadosEnsaio.velocidade = DadosEnsaio.config_velocidade;
          //updateVelocidadeEsteira();
          //ShowVelocidade();
          // DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
          //ShowTempo(DadosEnsaio.tempo);
          //showVelocidadeReal(322, 95, DadosEnsaio.velocidade);
          //showVelocidadeDefinida(402, 95, DadosEnsaio.config_velocidade);
          //showDistancia(DadosEnsaio.distanciaAcumulada);
        }

      } while ((enterPressed == false && (DadosEnsaio.velocidade <= 5.0)));
      // Fim do controle de MF

      timerStop(timer);
      enterPressed = false;
      DadosEnsaio.tempo = DadosEnsaio.config_tempo + interruptCounter1s;
      //if (DadosEnsaio.tempo <= 10000)
      //{
        flagFuncionamento = false;
        flagOn = false;
        onOff();
        ShowTempo(DadosEnsaio.tempo);
        //comando = VOLTAR;
        //ShowOpcoes();
        //escolheComandoTCFM();
        //return 1;
      //}
      //ShowTempo(DadosEnsaio.tempo);
      comando = PARAR;
      break;

    case VOLTAR:
      flagFuncionamento = false;
      flagOn = false;
      onOff();
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
