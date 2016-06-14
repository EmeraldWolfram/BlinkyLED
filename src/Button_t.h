#ifndef Button_t_H
#define Button_t_H

#include <stdlib.h>

#define IS_RELEASED 0
#define IS_PRESSED  !(IS_RELEASED)

typedef struct
{
  int btnState;
}Button_t;

Button_t* createButton();
//int getButton(Button_t* btn); mocked at Timer for easy mock

#endif // Button_t_H
