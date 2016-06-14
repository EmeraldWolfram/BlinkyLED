#include "unity.h"
#include "ErrorObject.h"
#include "CException.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ThrowError_throw_ERR_NOT_OPERATOR_should_get_an_error_object_containing_them(void){
  ErrorObject* err;
  Try{
    ThrowError(ERR_NULL_INPUT_LED, "Input LED cannot be NULL");
    TEST_FAIL_MESSAGE("Expecting ERR_NULL_INPUT_LED but none thrown.");
  }Catch(err){
    TEST_ASSERT_EQUAL(ERR_NULL_INPUT_LED, err->errorCode);
    TEST_ASSERT_EQUAL_STRING("Input LED cannot be NULL",  err->errorMsg);
    freeError(err);
  }
}
