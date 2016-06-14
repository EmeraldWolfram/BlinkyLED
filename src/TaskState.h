#ifndef TaskState_H
#define TaskState_H
#include "LED_t.h"
#include "ErrorObject.h"
#include "Timer.h"

#include <stdlib.h>

#define IS_RELEASED 0
#define IS_PRESSED  !(IS_RELEASED)

typedef struct
{
  int btnState;
}Button_t;

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

Button_t* createButton();
TaskState* createTaskState(int blinkTime, LED_t* led, Button_t* btn);
void buttonAndLED(TaskState* tsk);

#endif // TaskState_H
