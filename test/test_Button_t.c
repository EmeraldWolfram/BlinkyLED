#include "unity.h"
#include "Button_t.h"

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
