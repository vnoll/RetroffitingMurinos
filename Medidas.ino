#include "Medidas.h"

void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&timerMux);
  interruptCounter1s++;
  portEXIT_CRITICAL_ISR(&timerMux);

}
void calculadistancia()
{
  int seg1=0;
  static int oldseg1=0;
  seg1 = ((interruptCounter1s % 60) % 10);
  if (oldseg1 !=  seg1)
  {
    distancia = veloreal / 3.6;
    distanciatotal = distanciatotal + distancia;
    oldseg1 = seg1;
  }
}
void initTimer() {
  interruptCounter1s = 0;
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 1000000, true);
  timerAlarmEnable(timer);
}
void ZeraTimer() {
  interruptCounter1s = 0;
  Counter1Min = 0;
  Counter1Hour = 0;
}
