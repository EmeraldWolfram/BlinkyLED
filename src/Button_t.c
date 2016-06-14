#include "Button_t.h"

Button_t* createButton()
{
  Button_t* newButton = malloc(sizeof(Button_t));
  newButton->btnState = IS_RELEASED;
  
  return newButton;
}

