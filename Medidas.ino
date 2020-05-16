
#include "Medidas.h"

 
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter1s++;
  portEXIT_CRITICAL_ISR(&timerMux);
 
}
 
void initTimer() {

  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}
 
void timerRefresh() {

  if (interruptCounter1s >= 60){
    portENTER_CRITICAL(&timerMux);
    interruptCounter1s = 0;
    portEXIT_CRITICAL(&timerMux);
    Counter1Min++;
    if (Counter1Min == 60)  {
      Counter1Min = 0;
      Counter1Hour++;
      if (Counter1Hour > 11) {
        Counter1Hour = 0;
      }
    }
  }
}
