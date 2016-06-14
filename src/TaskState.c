#include "TaskState.h"



TaskState* createTaskState(int blinkTime, LED_t* led, Button_t* btn)
{
  TaskState* newState = malloc(sizeof(TaskState));
  
  newState->state         = RELEASED;
  newState->recordedTime  = 0;
  newState->interval      = blinkTime;
  newState->whichLED      = led;
  newState->whichButton   = btn;
  
  return newState;
}


void buttonAndLED(TaskState* tsk){
  int timeDiff;
  switch((tsk->state))
  {
    case RELEASED:
      if(getButton(tsk->whichButton) == IS_PRESSED)
      {
        turnLED(tsk->whichLED, ON);
        tsk->recordedTime = getTime();
        tsk->state  = PRESSED_ON;
      }
      break;
    case PRESSED_ON:
      if(getButton(tsk->whichButton) == IS_RELEASED)
      {
        tsk->state  = RELEASED_ON;
      }
      timeDiff = getTime() - (tsk->recordedTime);
      if(timeDiff >= tsk->interval)
      {
        turnLED(tsk->whichLED, OFF);
        tsk->recordedTime = getTime();
        tsk->state = PRESSED_OFF;
      }
      
      break;
    case PRESSED_OFF:
      if(getButton(tsk->whichButton) == IS_RELEASED)
      {
        tsk->state  = RELEASED_OFF;
      }
      timeDiff = getTime() - (tsk->recordedTime);
      if(timeDiff >= tsk->interval)
      {
        turnLED(tsk->whichLED, ON);
        tsk->recordedTime = getTime();
        tsk->state = PRESSED_ON;
      }
      break;
    case RELEASED_ON:
      if(getButton(tsk->whichButton) == IS_PRESSED)
      {
        turnLED(tsk->whichLED, OFF);
        tsk->state  = TURNING_OFF;
      }
      timeDiff = getTime() - (tsk->recordedTime);
      if(timeDiff >= tsk->interval)
      {
        turnLED(tsk->whichLED, OFF);
        tsk->recordedTime = getTime();
        tsk->state = RELEASED_OFF;
      }
      break;
    case RELEASED_OFF:
    
      break;
    case TURNING_OFF:
    
      break;
  }
}
