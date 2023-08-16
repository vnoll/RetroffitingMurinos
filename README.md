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

