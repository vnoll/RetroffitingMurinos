/* ALTERAÇÕES REALIZADAS:

01/09 - REALIZADO O RECEBIMENTO DO ENCODER DIRETAMENTE NA ESP (MEDIDAS.H E.INO), VERIFICADO O CALCULO
AGORA ESTÁ CORRETO E LEITURA DO ENCODER ATRAVÉS DO PINO 21 E PINO 5 PARA LEITURA EXTERNA

02/09 - ADICIONADO CONTROLE DE VELOCIDADE MELHOR PARA MAIORES VELOCIDADES, NECESSÁRIO TESTE.
INICIALIZAÇÃO DO PONTO DE ACESSO WIFI PARA REALIZAÇÃO DO SERVIDOR DE DADOS ATRAVÉS DO CELULAR E COMPUTADOR.

03/09 - ATUALIZAÇÃO: WEBSERVER NO IP 192.168.4.1 MOSTRA SOMENTE O DADO EM TEMPO REAL.

10/09 - ADICIONADO A FUNCAO DE ENVIAR INFORMAÇÕES AO EXCEL EM TEMPO REAL VIA SERIAL, ASSIM REALIZANDO O LOG
*/

#include <SPI.h>
#include "Main.h"
#include "stdlib.h" //Biblioteca de funções gerais e macro
#include "stdio.h"
#include <esp_task_wdt.h> //WatchDogTime da ESP
//#include <WiFi.h>
//#include <WebServer.h>

#include "MenuPrincipal.h"
#include "Medidas.h"
#include "Display.h"
#include "ModoManual.h"
#include "ModoTCFM.h"
#include "ModoTFA.h"


#define maisVelo 18        // Porta saida aumentar controle de  velocidade
#define menosVelo 19       // Porta saida diminuir controle de velocidade
#define botaoEmergencia 23 // Porta saída botão de liga e desliga
#define encoder_b1 21      // Porta de entrada do sinal do encoder
#define encoder_b2 5       // Porta para análise gráfica dos sinais

#define DESL_TITULO_DISPLAY_MODO_MANUAL -2
#define DESL_TITULO_DISPLAY_MODO_TFA 40
#define DESL_TITULO_DISPLAY_MODO_TCFM 25

unsigned long tempoState = millis();
unsigned long tempoModoTCFM = millis();

/*****************************************************************
      INFORMAÇÕES IMPORTANTES
      =======================
[ ] - IDE ARDUINO versão usada: 1.8.16
      VS Code
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
  Serial.println("Configurando pinagens ....");
  pinMode(ENTER, INPUT);
  pinMode(maisVelo, OUTPUT);
  pinMode(menosVelo, OUTPUT);
  pinMode(botaoEmergencia, OUTPUT);
  digitalWrite(maisVelo, LOW);
  digitalWrite(menosVelo, LOW);
  digitalWrite(botaoEmergencia, HIGH);
  pinMode(ENCODER_MOTOR_PIN, INPUT_PULLUP);
  pinMode(encoder_b2, OUTPUT);

  Serial.println("Configurando interrupções ....");
  attachInterrupt(ENCODER_MOTOR_PIN, encoderPinoB, RISING);
  attachInterrupt(ENTER, isr_enter, FALLING);
  
  Serial.println("Configurando Display ....");
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

  Serial.println("Configurando Timer ....");
  initTimer0();
  initTimer1Velo();

  //xTaskCreatePinnedToCore(updateServidor_Dados, /* Task function. */
  //                         "update",       /* String with name of task. */
  //                          10000,                 /* Stack size in bytes. */
  //                          NULL,                  /* Parameter passed as input of the task */
  //                          5,                     /* Priority of the task. */
  //                         &updateTaskOption,     /* task handle */
  //                          0);                    /* pinned to core */

  disableCore0WDT();
  disableCore1WDT();
}

void loop()
{
  switch (menu)
  {
  case PRINCIPAL:
  
    Serial.print("Escolha de modo ... ");
    menuPrincipal();    
    break;

  case MANUALL:
    Serial.print("Modo MANUAL ... ");
    modoManual(DESL_TITULO_DISPLAY_MODO_MANUAL, "MANUAL");    
    menu = PRINCIPAL;
    break;

  case TCFM:
    Serial.print("Modo TCFM ... ");
    modoTCFM(DESL_TITULO_DISPLAY_MODO_TCFM, "TCFM");
    menu = PRINCIPAL;
    break;

  case TFAA:
    Serial.print("Modo TFA ... ");
    modoTFA(DESL_TITULO_DISPLAY_MODO_TCFM, "TFA");
    menu = PRINCIPAL;
    break;

  default:
    menu = PRINCIPAL;
    break;
  }
}
