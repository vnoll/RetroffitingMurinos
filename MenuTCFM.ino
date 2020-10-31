void menuTCFM()
{
  if (primeiravez)
  {
    tft.fillScreen(KHAKI);//LIMPA A TELA
    tft.drawRoundRect(80, 5, 315, 45, 10, GREY); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(81, 6, 313, 43, 8, LGREEN);
    showmsgf(105 + X, 40, 1, BLACK, &FreeSansBold18pt7b, "MODO ", modo);

    tft.drawRoundRect(20, 55, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(21, 56, 273, 53, 8, GELO);
    showmsg(35, 90, 1, BLACK, &FreeSansBold12pt7b, "VELOCIDADE (Km/h):");
    tft.drawRoundRect(305, 55, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 56, 158, 53, 8, GELO);

    tft.drawRoundRect(20, 125, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(21, 126, 273, 53, 8, GELO);
    showmsg(98, 160, 1, BLACK, &FreeSansBold12pt7b, "DISTANCIA (m): ");
    tft.drawRoundRect(305, 125, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 126, 158, 53, 8, GELO);

    tft.drawRoundRect(20, 195, 275, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(21, 196, 273, 53, 8, GELO);
    showmsg(150, 230, 1, BLACK, &FreeSansBold12pt7b, "TEMPO (s): ");
    tft.drawRoundRect(305, 195, 160, 55, 10, tft.color565(0, 0, 0)); // (x, y, largura, altura, arredondamento)
    tft.fillRoundRect(306, 196, 158, 53, 8, GELO);
    ZeraTimer();
    ShowTempo();
    primeiravez = ON;
    showVelocidadeReal(362, 95, veloreal);
    primeiravez = ON;
    showDistancia();
    primeiravez = OFF;
  }
}
