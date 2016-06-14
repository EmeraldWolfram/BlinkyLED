#include "TaskState.h"

Button_t* createButton(){
  Button_t* newButton = malloc(sizeof(Button_t));
  newButton->btnState = IS_RELEASED;
  
  return newButton;
}

TaskState* createTaskState(int blinkTime, LED_t* led, Button_t* btn){
  TaskState* newState = malloc(sizeof(TaskState));
  
  newState->state         = RELEASED;
  newState->recordedTime  = 0;
  newState->interval      = blinkTime;
  newState->whichLED      = led;
  newState->whichButton   = btn;
  
  return newState;
}


void buttonAndLED(TaskState* tsk){
  switch((tsk->state))
  {
    case RELEASED:
    if(tsk->whichButton->btnState == IS_PRESSED)
    {
      turnLED(tsk->whichLED, ON);
      tsk->recordedTime = getTime();
      tsk->state  = PRESSED_ON;
    }
    break;
    case PRESSED_ON:
    
    break;
    case PRESSED_OFF:
    
    break;
    case RELEASED_ON:
    
    break;
    case RELEASED_OFF:
    
    break;
    case TURNING_OFF:
    
    break;
  }
}
