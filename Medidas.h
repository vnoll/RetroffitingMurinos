#ifndef __MEDIDAS__HEADER__
#define __MEDIDAS__HEADER__

#include "Main.h"

#define ENCODER_DT 34
#define ENCODER_CLK 39
#define ENTER 35

#include <RotaryEncoder.h>
RotaryEncoder encoder(ENCODER_DT, ENCODER_CLK);
#define timermaximo 43200

volatile int oldinterruptCounter1s = 0 , interruptCounter1s = 0;
int Counter1Min = 0;
int Counter1Hour = 0;
int pos = 1;
int newPos = 1;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void initTimer();
void timerRefresh();
void ZeraTimer();
void updateDistancia();
void updateVelocidadeEsteira();

#endif
