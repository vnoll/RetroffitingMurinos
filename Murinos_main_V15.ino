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
  encoder.setPosition(1);
}

void loop()
{
  timerRefresh();
  Serial.println("passei no loop");
  if (Serial.available() > 0)
  {
    String dadoLido = Serial.readString();
    Serial.println(dadoLido);
  }
  switch (menu)
  {
    case principal:
      menuPrincipal();
      changeMenu();
      break;

    case manual:
      mudabotao();
      pressionabotao();
	  Serial.println("%d:%d:%d",Counter1Hour, Counter1Min,interruptCounter1s);

    break;

    case tcfm:
      mudabotao();
      pressionabotao();
      break;

    case tfa:
      mudatfa();
      pressionatfa();
      break;

    case tfagenerico:
      mudabotao();
      pressionabotao();
      break;
  }
  if (selecionado == 1 and (menu != 0 || menu != 3))
  {
    ShowTempo();
  }
}
void changeMenu()
{
  //Lê se o botão foi pressionado e levanta a flag
  if (!digitalRead(ENTER)) pressbt = 1;
  if (digitalRead(ENTER) && pressbt)
  {
    //abaixa a flag
    pressbt = 0;
    switch (pos)
    {
      case manual: //Entra no menu MANUAL
        menu = manual;
        primeiravez = 1; //Levanta a flag do menu
        X = -2;//Ajusta a posição do título
        modo = "MANUAL";
        menuGenerico();
        encoder.setPosition(4);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO
        break;

      case tcfm: //Entra no menu TCFM
        menu = tcfm;
        modo = "TCFM";
        X = 25;//Ajusta a posição do título
        primeiravez = 1;//Levanta a flag do menu
        encoder.setPosition(4);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO
        menuGenerico();
        break;

      case tfa: //Entra no menu TFA
        velo=0;
        TEMPOTOTAL=0;
        menu = tfa;
        modo = "TFA";
        X = 40;//Ajusta a posição do título
        primeiravez = 1;//Levanta a flag do menu
        encoder.setPosition(4);//RESETA O CURSOR PARA A PRIMEIRA POSIÇÃO
        menuTFA();
        break;
    }
  }
}
