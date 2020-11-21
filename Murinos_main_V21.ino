#include <SPI.h>          // f.k. for Arduino-1.5.2
#include "Main.h"

/*****************************************************************
parei o projeto de software em 17/11/2020
Estou usando o VSCode para codificar e uma pasta copia para testar
As alterações que foram testadas e, se aprovadas, são inseridas no GIT
O que falta fazer:
[x] - achar uma maneira de guardar dados permanentemente - NVS
[ ] - permitir baixar os dados dos ensaios para o PC via serial
[ ] - criar tela de configuração em cada modo
[ ] - criar funções de controle no modo manuall
[ ] - evitar o loop de controle preso num while (WDTimer)
[ ] - pensar em criar uma pagina estatica WEB para log do sistema
[ ] - criar opção de relatório do experimento na tela e na WEB
[ ] - depois disso, então implementar os 2 outros modos de controle
[ ] - separar melhor as funções de mostrar na tela (show*)
[ ] - usar a flash para armazenar dados de inicialização ou do experimento (NVS)

*******************************************************************/
void setup_NVS()
{
  // based in http://www.lucadentella.it/en/2017/06/03/esp32-19-nvs/

  Serial.println("inicializando Non-volatile Storage");
  esp_err_t err;
  err = nvs_flash_init();
  Serial.print("Non-volatile Storage = ");
  if (err == ESP_OK ) Serial.println("ESP_OK");
  else Serial.println("erro");

  const esp_partition_t* nvs_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA, ESP_PARTITION_SUBTYPE_DATA_NVS, NULL);      
  if(!nvs_partition) Serial.println("FATAL ERROR: No NVS partition found\n");
  else Serial.println("NVS partition found\n");

  /* rodar uma vez só - depois retirar
  //  ===============================
  err = (esp_partition_erase_range(nvs_partition, 0, nvs_partition->size));
  if(err != ESP_OK) Serial.println("FATAL ERROR: Unable to erase the partition\n");
  else Serial.println("Erase all partition\n");
  */
    
  err = nvs_open("storage", NVS_READWRITE, &h_nvs);
  if (err != ESP_OK) Serial.println("FATAL ERROR: Unable to open NVS\n");
  else Serial.println("Open NVS\n");

  // exemplo de escrita e leitura
  // escreve na memoria local
  // commit na flashes
  // le da flash

  /*

  err = nvs_set_i8(h_nvs,"velocidade", (int8_t) 127);
  err = nvs_set_i8(h_nvs,"tempo_em_seg", (int8_t) 100);
  if (err != ESP_OK) Serial.println("FATAL ERROR: Unable to write NVS\n");
  else Serial.println("write values to NVS\n");

  err = nvs_commit(h_nvs);
  if (err != ESP_OK) Serial.println("FATAL ERROR: Unable to commit NVS\n");
  else Serial.println("commit values to NVS\n");
  
  int8_t out_value;
  err = nvs_get_i8(h_nvs,"velocidade", &out_value);
  Serial.print("velocidade = ");
  Serial.println(out_value);
  */

}


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
  setup_NVS();
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

