const int encoder_b1 = 2; // Entrada pino 2 Nano
const int encoder_b2 = 3; // Entrada pino 3 Nano
float contador_pulso;
float direction = 1.000;
float speedkmh;

void encoderPinoB()
{
  contador_pulso += 1;
  direction = digitalRead(encoder_b1) == digitalRead(encoder_b2) ? 1.000 : 1.000;
}

void setup()
{
  Serial.begin(9600);
  pinMode(encoder_b1, INPUT_PULLUP);
  pinMode(encoder_b2, INPUT_PULLUP);
  attachInterrupt(0, encoderPinoB, RISING);
}

void loop()
{
  float speed = (float)contador_pulso / 1000.00 * 60.00;       // RPM equação, resolucao encoder
  float speedkmh = ((1.000 * speed * 0.1885 * 0.051) * 0.335); // Equação velocidade, que é rotação * 0.1885 * diametro em metros
  //33.5 % a menos em relacao a outra polia

 // Serial.println(speedkmh);
  Serial.write((byte *)&speedkmh, 4);
  contador_pulso = 0.000; // Limpa sempre que mostrar a nova contagem
  delay(500); //Envio a cada 1 segundo
}
