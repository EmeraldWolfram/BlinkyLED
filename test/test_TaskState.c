#include "unity.h"
#include "TaskState.h"
#include "LED_t.h"
#include "ErrorObject.h"



void setUp(void)
{
}

void tearDown(void)
{
}

//Create a button with state IS_RELEASED
void test_createButton(void)
{ 
  Button_t* btn = createButton();
  
  TEST_ASSERT_NOT_NULL(btn);
  TEST_ASSERT_EQUAL(btn->btnState, IS_RELEASED);
}

void test_createTaskState(void)
{ 
  Button_t* btn = createButton();
  LED_t* gLed   = createLED();
  TaskState* tState = createTaskState(RELEASED, 250, gLed, btn);
  
  TEST_ASSERT_EQUAL(tState->state, RELEASED);
  TEST_ASSERT_EQUAL(tState->recordedTime, 0);
  TEST_ASSERT_EQUAL(tState->interval, 250);
  TEST_ASSERT_EQUAL_PTR(tState->whichLED, gLed);
  TEST_ASSERT_EQUAL_PTR(tState->whichButton, btn);
}
//***********************************************************************

void test_buttonAndLED(void)
{
  TaskState* tState = createTaskState(RELEASED, 250, createLED(), createButton());
  
  buttonAndLED(tState);
}



