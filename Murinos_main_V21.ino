#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Main.h"

void setup()
{
  Serial.begin(9600);
  pinMode(ENTER, INPUT);
  attachInterrupt(ENTER, isr_enter, FALLING); 
  uint16_t ID = tft.readID();
  tft.begin(ID);
  if (ID == 0xD3D3) ID = 0x9481;
  tft.setRotation(1);
  showAbertura();
  encoder.setPosition(1);
  menu = PRINCIPAL;
  comando = PARAR;
  memset(pDadosEnsaio,0, sizeof(DadosEnsaio)); 
  initTimer();
}

void loop()
{  
  switch (menu)
  {
    case PRINCIPAL:
        
        menuPrincipal();
        Serial.print("Menu ATUAL: ");
        Serial.println(menu);
        Serial.print("Comando ATUAL: ");
        Serial.println(comando);
        break;

    case MANUALL:
        modoManual(DESL_TITULO_DISPLAY_MODO_MANUAL,"MANUAL");     
        Serial.print("Menu  MANUALL ... ");
        menu = PRINCIPAL;
      break;

    case TCFM:
        Serial.print("Menu  TCFM ... ");
        menu = PRINCIPAL;
        delay(1000);
      break;

    case TFA:
        Serial.print("Menu  TFA ... ");
        menu = PRINCIPAL;
        delay(1000);
      break;

    default:
      menu = PRINCIPAL;
      break;
  }
}

