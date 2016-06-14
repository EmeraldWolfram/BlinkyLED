#include "unity.h"
#include "LED_t.h"
#include "ErrorObject.h"
#include <stdlib.h>


void setUp(void)
{
}

void tearDown(void)
{
}

//Create an LED type structure
void test_createLED(void)
{
  LED_t* led = createLED();
  
  TEST_ASSERT_FALSE(led->ledState);
}

//turn LED On when ON input received
void test_turnLED_to_turn_ON_RED_LED(void)
{
	LED_t* redLed = createLED();
  
  turnLED(redLed, ON);
  TEST_ASSERT_TRUE(redLed->ledState);
}

//turn LED Off when OFF input received
void test_turnLED_to_turn_OFF_RED_LED(void)
{
	LED_t* redLed = createLED();
  
  turnLED(redLed, OFF);
  TEST_ASSERT_FALSE(redLed->ledState);
}

//turn LED on even last bit was zero
void test_turnLED_to_turn_ON_RED_LED_with_binary10(void)
{
  LED_t* redLed = createLED();
  
  turnLED(redLed, 2);
  TEST_ASSERT_TRUE(redLed->ledState);
}


//receiving null should throw ERR_NULL_INPUT_LED
void test_turnLED_with_null_input(void)
{
  ErrorObject* err;
  Try
  {
    turnLED(NULL, 2);
    TEST_FAIL_MESSAGE("Expected ERR_NULL_INPUT_LED but none thrown")
  } Catch (err)
  {
    TEST_ASSERT_EQUAL(err->errorCode, ERR_NULL_INPUT_LED);
    TEST_ASSERT_EQUAL_STRING(err->errorMsg, "Input LED was NULL");
    freeError(err);
  }
}