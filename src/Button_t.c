#include "Button_t.h"

Button_t* createButton()
{
  Button_t* newButton = malloc(sizeof(Button_t));
  newButton->state      = IDLE;
  newButton->prevState  = readButton();
  newButton->output     = IS_RELEASED;
  newButton->curState   = IS_RELEASED;
  newButton->recordedTime = 0;
  
  return newButton;
}

void buttonFSM(Button_t* button){
  int readBtn;
  switch(button->state){
    case IDLE:
      readBtn = readButton();
      if(button->prevState != readBtn)
      {
        button->recordedTime  = getTime();
        button->prevState     = readBtn;
        button->state         = WAIT;
      }
      break;
    case WAIT:
      if((getTime() - button->recordedTime) > 99)
      {
        button->curState  = readButton();
        if(button->prevState == button->curState)
        {
          button->output  = button->curState;
          button->state   = IDLE;
        }
        else
        {
          button->prevState = button->curState;
          button->state     = IDLE;
        }
      }
      break;
  }
}

int getButton(Button_t* btn)
{
    return btn->output;
}
