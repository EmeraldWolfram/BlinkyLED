#ifndef TaskState_H
#define TaskState_H
#include "LED_t.h"
#include "Button_t.h"
#include "ErrorObject.h"
#include "AllMock.h"

#include <stdlib.h>

typedef enum 
{
  RELEASED,
  PRESSED_ON,
  PRESSED_OFF,
  RELEASED_ON,
  RELEASED_OFF,
  TURNING_OFF
}FsmState;

typedef struct
{
  FsmState      state;
  unsigned int  recordedTime;
  int           interval;
  LED_t*        whichLED;
  Button_t*     whichButton;
}TaskState;


TaskState* createTaskState(int blinkTime, LED_t* led, Button_t* btn);
void buttonAndLED(TaskState* tsk);

#endif // TaskState_H
