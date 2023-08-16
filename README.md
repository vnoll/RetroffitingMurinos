# RetroffitingMurinos
Retrofitting de esteira de uso humano, adequando-a para testes ergométricos em ratos e camundongos de laboratório
para uso da UDESC-CEFID LAPEX

### IDE utilizada
Arduino IDE ultima versão

### Hardware Utilizado
- ESP32 para controle
- Display LCD TFT 3.2"  240 x 320 pixels (IIL9341)
- Encoder rotativo de 1000 linhas/volta

### Bibliotecas que tem que ser adiciondas:
- Adafruit_GFX_Library
- Adafruit_TFTLCD
- MCUFRIEND_kbv-master
- RotaryEncoder-master
- WiFi

### Arquivos
- Murinos_main_V35.ino
- Display.ino
- Medidas.ino
- MenuPrincipal.ino
- ModoManual.ino
- ModoTFA.ino
- ModoTCFM.ino

### TROCA DE ARQUIVOS
- A bibliteca de controle do Display LCD ILI9341
- que é a MCUFRIENDS_kbv, tem 2 arquivos que 
- devem trocados pelos arquivos:
- "mcufriend_shield.h" e "mcufriend_special.h" 
- contidos neste repositório

### PINAGEM FINAL ENTRE LCD E ESP-32
A montagem final ficou com a seguinte configuração (dentro do arquivo mcufriend_special.h)
Como a pinagem mudou, foi por isso que mudamos os arquivos "mcufriend_shield.h" e "mcufriend_special.h"

LCD_RD  4   
LCD_WR  2  
LCD_RS 15  
LCD_CS 33  
LCD_RST 32  
LCD_D0 12  
LCD_D1 13  
LCD_D2 16  
LCD_D3 17  
LCD_D4 5   
LCD_D5 26  
LCD_D6 27  
LCD_D7 14  

