#ifndef Button_t_H
#define Button_t_H

#include <stdlib.h>
#include "AllMock.h"

#define IS_RELEASED 0
#define IS_PRESSED  !(IS_RELEASED)

typedef enum{
  IDLE,
  WAIT
} State;

typedef struct
{
  State state;
  int curState;
  int prevState;
  int output;
  int recordedTime;
} Button_t;

Button_t* createButton();
void buttonFSM(Button_t* button);
int getButton(Button_t* btn); //mocked at Timer for easy mock

#endif // Button_t_H
