#ifndef __MEDIDAS__HEADER__
#define __MEDIDAS__HEADER__

volatile int interruptCounter1s = 0;
int Counter1Min = 0;
int Counter1Hour = 0;
 
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void initTimer();
void timerRefresh();

#endif
