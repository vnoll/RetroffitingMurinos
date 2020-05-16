#include <SPI.h>          // f.k. for Arduino-1.5.2

#include "Main.h"
#include "Display.h"
#include "Medidas.h"

void setup() 
{
  Serial.begin(9600);  
  uint16_t ID = tft.readID();
  tft.begin(ID);
  if (ID == 0xD3D3) ID = 0x9481;
  tft.setRotation(1);
  showAbertura();
  initTimer();
}

void loop() 
{
    if (Serial.available() > 0) {
      String dadoLido = Serial.readString();
      Serial.println(dadoLido);
    }
    timerRefresh();  // tem que ser chamada em menos de 1 segundo
	  menuprincipal();
}
