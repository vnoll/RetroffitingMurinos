#ifndef __MEDIDAS__HEADER__
#define __MEDIDAS__HEADER__

#include <RotaryEncoder.h>
RotaryEncoder encoder(34, 39);
#define ENTER 35
#define timermaximo 43200

volatile int oldinterruptCounter1s = 0 , interruptCounter1s = 0;
int Counter1Min = 0;
int Counter1Hour = 0;

hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void initTimer();
void initTimer2();
void timerRefresh();
void ContaTempo();
void calculadistancia();

#endif
