#ifndef __MAIN__HEADER__
#define __MAIN__HEADER__

#include "stdlib.h"
#include "stdio.h"
#include <esp_task_wdt.h> 

#include "MenuPrincipal.h"
#include "Medidas.h"
#include "Display.h"
#include "ModoManual.h"
#include "ModoTCFM.h"
#include "ModoTFA.h"

#define DESL_TITULO_DISPLAY_MODO_MANUAL -2
#define DESL_TITULO_DISPLAY_MODO_TFA 40
#define DESL_TITULO_DISPLAY_MODO_TCFM 25

/****************************************************************
 * a estrutura de dados é global e pertence a todo o projeto    *
 * mudanças aqui implicam em mudanças globais                   *
 *                                                              *
 * 1) menu --> Indicação do menu atual                          *
 * 2) comando --> Indicação comando selecionado                 *
 * 3) DadosEnsaio --> Estrutura que mantém os dados atuais      *
 * 4) enterPressed --> atualizado na int quando for ENTER       *
 * **************************************************************/

enum menus
{
  PRINCIPAL,
  MANUALL,
  TCFM,
  TFAA
};
enum menus menu;

enum comandos
{
  INICIAR,
  PARAR,
  VOLTAR,
  CONFIRMAR
};
enum comandos comando;

enum comandovelocidade
{
  aumentarVelocidade,
  diminuirVelocidade,
  mesmaVelocidade
};
enum comandovelocidade Velocidade;

struct Dados
{
  float velocidade;
  float distanciaAcumulada;
  float distancia1s;
  long tempo;
  float config_velocidade;
  long config_tempo;
};
struct Dados DadosEnsaio;
struct Dados *pDadosEnsaio = &DadosEnsaio;

bool enterPressed = false;
bool flagFuncionamento = false;
bool pulsoAtivo = false;
bool flagOn = false;

// task handler
TaskHandle_t updateTaskOption;

/* **************************************************************
*   FIM DA ESTRUTURA DE DADOS GLOBAIS                            *
*****************************************************************/

/*  Interrupção ao selecionar o botão Enter*/
void IRAM_ATTR isr_enter()
{
  detachInterrupt(digitalPinToInterrupt(ENTER));
  enterPressed = false;
  if (digitalRead(ENTER) == LOW)
  {
    for (int x = 0; x < 5000; x++)
      ;
    if (digitalRead(ENTER) == LOW)
      enterPressed = true;
    else
      enterPressed = false;
  }
  attachInterrupt(ENTER, isr_enter, FALLING);
}

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#endif
