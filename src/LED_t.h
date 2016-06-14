#ifndef LED_t_H
#define LED_t_H
#include "ErrorObject.h"
#include "CException.h"
#include <stdlib.h>

#define OFF 0
#define ON  !(OFF)


typedef struct
{
  int  ledState;
}LED_t;

LED_t* createLED();
void turnLED(LED_t* led, int actionToLED);


#endif // LED_t_H
