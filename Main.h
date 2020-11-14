#ifndef __MAIN__HEADER__
#define __MAIN__HEADER__

#include "stdlib.h"
#include "stdio.h"

#include "MenuPrincipal.h"
#include "Medidas.h"
#include "Display.h"
#include "ModoManual.h"

#define DESL_TITULO_DISPLAY_MODO_MANUAL -2
#define DESL_TITULO_DISPLAY_MODO_TFA 40
#define DESL_TITULO_DISPLAY_MODO_TCFM 25

/****************************************************************
 * a estrutura de dados é global e pertence a todo o projeto    *
 * mudanças aqui implicam em mudanças globais                   *
 *                                                              *
 * 1) menu --> indica em qual menu estou                        *
 * 2) comando --> indica qual o ultimo comando dado             *
 * 3) DadosEnsaio --> estrutuRa que mantém os dados atuais      *
 * 4) enterPressed --> atualizado na int quando for ENTER       *
 * **************************************************************/

enum menus {PRINCIPAL,MANUALL,TCFM,TFA};
enum menus menu;

enum comandos {INICIAR, PARAR, VOLTAR, CONFIRMAR};
enum comandos comando;

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
struct Dados * pDadosEnsaio = &DadosEnsaio;

bool enterPressed = false;

/* **************************************************************
*   FIM DA ESTRUTURA DE DADOS GLOBAIS                            *
*****************************************************************/

/*  aqui ocorre a interrupção toda vez que o botão é pressionado*/
void IRAM_ATTR isr_enter() {
  enterPressed = false;
  delay(200);
  if (digitalRead(ENTER)==LOW)
  {
    delay(100);
    if (digitalRead(ENTER)==LOW) enterPressed = true;
    else enterPressed = false;
  }
}

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#endif
