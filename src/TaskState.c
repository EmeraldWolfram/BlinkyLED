#include "TaskState.h"



TaskState* createTaskState(int blinkTime, LED_t* led, Button_t* btn)
{
  TaskState* newState = malloc(sizeof(TaskState));
  
  newState->state           = RELEASED;
  newState->recordedTime    = 0;
  newState->interval        = blinkTime;
  newState->whichLED        = led;
  newState->whichButton     = btn;
  newState->buttonReleased  = TRUE;
  
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
        tsk->state        = PRESSED_ON;
        tsk->buttonReleased = FALSE;
      }
      break;
    case PRESSED_ON:
      if(getButton(tsk->whichButton) == IS_RELEASED)
        tsk->buttonReleased = TRUE;
      else 
      {
        if(tsk->buttonReleased == TRUE) 
          tsk->state  = TURNING_OFF;
          tsk->buttonReleased = FALSE;
          turnLED(tsk->whichLED, OFF);
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
        tsk->buttonReleased = TRUE;
      else
      {
        if(tsk->buttonReleased == TRUE)
        {
            tsk->state = TURNING_OFF;
            tsk->buttonReleased = FALSE;
            turnLED(tsk->whichLED, OFF);
        }
      }
      timeDiff = getTime() - (tsk->recordedTime);
      if(timeDiff >= tsk->interval)
      {
        turnLED(tsk->whichLED, ON);
        tsk->recordedTime = getTime();
        tsk->state = PRESSED_ON;
      }
      break;
    case TURNING_OFF:
      if(getButton(tsk->whichButton) == IS_RELEASED)
      {
        tsk->buttonReleased = TRUE;
        tsk->state  = RELEASED;
      }
      break;
  }
}
