#include "LED_t.h"

LED_t* createLED()
{
  LED_t* newLED = malloc(sizeof(LED_t));
  newLED->ledState = OFF;
  
  return newLED;
}

void turnLED(LED_t* led, int actionToLED)
{
  if(led == NULL)
  {
    ThrowError(ERR_NULL_INPUT_LED, "Input LED was NULL");
  }
  led->ledState = actionToLED;
}
