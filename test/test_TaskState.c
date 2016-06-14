#include "unity.h"
#include "TaskState.h"
#include "LED_t.h"
#include "ErrorObject.h"
#include "mock_Timer.h"

unsigned int fake_getTime()
{
  return 10;
}

void setUp(void)
{
  getTime_StubWithCallback(fake_getTime);
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
  TaskState* tState = createTaskState(250, gLed, btn);
  
  TEST_ASSERT_EQUAL(tState->state, RELEASED);
  TEST_ASSERT_EQUAL(tState->recordedTime, 0);
  TEST_ASSERT_EQUAL(tState->interval, 250);
  TEST_ASSERT_EQUAL_PTR(tState->whichLED, gLed);
  TEST_ASSERT_EQUAL_PTR(tState->whichButton, btn);
}
//====================================================================================
/**************************************************************
  This test make sure the buttonAndLED function will only turn
  the LED ON when the button IS_PRESSED
 **************************************************************/
void test_buttonAndLED(void)
{
  TaskState* tState = createTaskState(250, createLED(), createButton());
  buttonAndLED(tState);
  TEST_ASSERT_FALSE(tState->whichLED->ledState);
  TEST_ASSERT_EQUAL(tState->state, RELEASED);
  TEST_ASSERT_EQUAL(tState->recordedTime, 0);
  
  tState->whichButton->btnState = IS_PRESSED;
  
  buttonAndLED(tState);
  TEST_ASSERT_TRUE(tState->whichLED->ledState);
  TEST_ASSERT_EQUAL(tState->state, PRESSED_ON);
  TEST_ASSERT_EQUAL(tState->recordedTime, 10);
}




