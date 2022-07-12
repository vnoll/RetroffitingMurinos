# RetroffitingMurinos
Retrofitting de esteira de uso humano, adequando-a para testes ergométricos em ratos e camundongos de laboratório
para uso da UDESC-CEFID LAPEX

### IDE utilizada
Arduino IDE ultima versão

### Hardware Utilizado
- ESP32 para controle
- Display LCD TFT 3.2"  240 x 320 pixels (IIL9341)
- Encoder rotativo de 1000 linhas/volta
- Arduino nano para medir a velocidade a cada 0.5 segundo
- Entre Arduino Nano e a ESP32 tem-se uma comunicação serial

### Bibliotecas que tem que ser adiciondas:
- Adafruit_GFX_Library
- Adafruit_TFTLCD
- MCUFRIEND_kbv-master
- RotaryEncoder-master

### Arquivos
- Murinos_main.ino
- Display.ino
- Medidas.ino
- MenuPrincipal.ino
- ModoManual.ino

