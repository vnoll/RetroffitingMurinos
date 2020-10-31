#include <SPI.h>          // f.k. for Arduino-1.5.2

#include "Main.h"
#include "Display.h"
#include "Medidas.h"

void setup()
{
  pinMode(ENTER, INPUT);
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  if (ID == 0xD3D3) ID = 0x9481;
  tft.setRotation(1);
  //Abertura();
  initTimer();
  encoder.setPosition(manual);
}

void loop()
{
  if (Serial.available() > 0)
  {
    String dadoLido = Serial.readString();
    Serial.println(dadoLido);
  }
  switch (menu)
  {
    case principal:
      menuPrincipal();
      if (BOTAOPRESSIONADO == OFF)
      {
        mudaopcoes();
      }
      changeMenu();
      break;

    case manual:
      if (SELECIONAVELOCIDADE != ON)
      {
        pressionabotaomanual();
        if (BOTAOPRESSIONADO == OFF)
        {
          mudabotaomanual();
        }
      }
      break;

    case tcfm:
      if (BOTAOPRESSIONADO == OFF)
      {
        mudabotao();
      }
      pressionabotao();
      break;

    case tfa:
      if (BOTAOPRESSIONADO == OFF)
      {
        mudatfa();
      }
      pressionatfa();
      break;

    case tfagenerico:
      if (BOTAOPRESSIONADO == OFF)
      {
        mudabotao();
      }
      pressionabotao();
      break;
  }
  if (playtime == ON and (menu != principal || menu != tfa))
  {
    showDistancia();
  }
  if (playtime == ON and (menu != principal || menu != tfa))
  {
    ShowTempo();
  }
  if (playtime == ON and (menu != principal || menu != tfa))
  {
    if (Serial.available() > 0)
    {
      ftemp = Serial.read();
      Serial.println(ftemp);
      char b[5];
      String str;
      str = String(ftemp);
      str.toCharArray(b, 5);
      Serial.println(b);
      veloreal  = atof(b);
      Serial.println(veloreal);
      showVelocidadeReal(322, 95, veloreal);
    }
    showVelocidadeReal(322, 95, veloreal);
  }
  if (SELECIONAVELOCIDADE == ON && menu == manual)
  {
    mudavelocidade();
    //Lê se o botão foi pressionado e levanta a flag
    if (!digitalRead(ENTER)) BOTAOPRESSIONADO = ON;
    if (digitalRead(ENTER) && BOTAOPRESSIONADO)
    {
      //abaixa a flag
      BOTAOPRESSIONADO = OFF;
      if (BOTAOPRESSIONADO == OFF)
      {
        primeiravez = ON;
        SELECIONAVELOCIDADE = OFF;
        tft.drawRoundRect(385, 55, 80, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
        tft.fillRoundRect(386, 56, 78, 53, 8, GELO);
        showVelocidadeDefinida(402, 95, velo);
      }
    }
  }
  if (interruptCounter1s >= timermaximo)
  {
    interruptCounter1s = 0;
  }
}
void changeMenu()
{
  //Lê se o botão foi pressionado e levanta a flag
  if (!digitalRead(ENTER)) BOTAOPRESSIONADO = ON;
  if (digitalRead(ENTER) && BOTAOPRESSIONADO)
  {
    //abaixa a flag
    BOTAOPRESSIONADO = OFF;
    switch (pos)
    {
      case manual: //Entra no menu MANUAL
        menu = manual;
        velo = 0;
        modo = "MANUAL";
        primeiravez = ON; //Levanta a flag do menu
        X = -2;//Ajusta a posição do título
        menuGenerico();
        encoder.setPosition(RESET);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO
        break;

      case tcfm: //Entra no menu TCFM
        menu = tcfm;
        modo = "TCFM";
        primeiravez = ON;//Levanta a flag do menu
        X = 25;//Ajusta a posição do título
        encoder.setPosition(RESET);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO
        menuTCFM();
        break;

      case tfa: //Entra no menu TFA
        menu = tfa;
        modo = "TFA";
        primeiravez = ON;//Levanta a flag do menu
        velo = 0;
        TEMPOTOTAL = 0;
        encoder.setPosition(RESET);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO
        menuTFA();
        break;
    }
  }
}
