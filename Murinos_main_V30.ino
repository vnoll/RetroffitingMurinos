#include <SPI.h>
#include "Main.h"
#include "stdlib.h" //Biblioteca de funções gerais e macro
#include "stdio.h"
#include <esp_task_wdt.h>   //WatchDogTime da ESP
#include <HardwareSerial.h> // Inclusão biblioteca modificada para comunicação com o Nano

#include "MenuPrincipal.h"
#include "Medidas.h"
#include "Display.h"
#include "ModoManual.h"
#include "ModoTCFM.h"
#include "ModoTFA.h"

#define maisVelo 18  // Porta saida aumentar controle de  velocidade
#define menosVelo 19 //Porta saida diminuir controle de velocidade
#define botaoEmergencia 23 //Porta saída botão de liga e desliga

#define DESL_TITULO_DISPLAY_MODO_MANUAL -2
#define DESL_TITULO_DISPLAY_MODO_TFA 40
#define DESL_TITULO_DISPLAY_MODO_TCFM 25

unsigned long tempoState = millis();



/*****************************************************************
      INFORMAÇÕES IMPORTANTES
      =======================
[ ] - IDE ARDUINO, versão usada: 1.8.1
      PROCESSADOR ESP-WROOM-32, 40 MHz Flash internal
      Placa: ESP32 Dev Module
      upload speed: 921600
      CPU frequency: 80 MHZ (WiFI/BT)
      Flash frequency: 40 MHZ
      Flash Mode: QIO
      Flash Size: 4MB(32MB)
[ ] - https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers --> driver serial ESP-WROOM-32

*******************************************************************/

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 21, 22);
  pinMode(ENTER, INPUT);
  pinMode(maisVelo, OUTPUT);
  pinMode(menosVelo, OUTPUT);
  pinMode(botaoEmergencia,OUTPUT);
  digitalWrite(maisVelo, LOW);
  digitalWrite(menosVelo, LOW);
  digitalWrite(botaoEmergencia,HIGH);

  attachInterrupt(ENTER, isr_enter, FALLING);
  uint16_t ID = tft.readID();
  tft.begin(ID);
  if (ID == 0xD3D3)
    ID = 0x9481;
  tft.setRotation(1);
  showAbertura();
  encoder.setPosition(1);
  menu = PRINCIPAL;
  comando = PARAR;
  memset(pDadosEnsaio, 0, sizeof(DadosEnsaio));
  initTimer();

  xTaskCreatePinnedToCore(updateTask_Velocidade, /* Task function. */
                          "updateTaskVel",       /* String with name of task. */
                          10000,                 /* Stack size in bytes. */
                          NULL,                  /* Parameter passed as input of the task */
                          5,                     /* Priority of the task. */
                          &updateTaskOption,     /* task handle */
                          0);                    /* pinned to core */

  disableCore0WDT();
  disableCore1WDT();
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
    modoManual(DESL_TITULO_DISPLAY_MODO_MANUAL, "MANUAL");
    Serial.print("Menu  MANUALL ... ");
    menu = PRINCIPAL;
    break;

  case TCFM:
    modoTCFM(DESL_TITULO_DISPLAY_MODO_TCFM, "TCFM");
    Serial.print("Menu  TCFM ... ");
    menu = PRINCIPAL;
    break;

  case TFAA:
    modoTFA(DESL_TITULO_DISPLAY_MODO_TCFM, "TFA");
    Serial.print("Menu  TFA ... ");
    menu = PRINCIPAL;
    break;

  default:
    menu = PRINCIPAL;
    break;
  }
}