#include "unity.h"
#include "Button_t.h"
#include "mock_AllMock.h"

int* buttonTable;
unsigned int* timeTable = NULL;

unsigned int fake_getTime()
{
  unsigned int time = *timeTable;
  timeTable++;
  return time;
}

int fake_readButton(){
  int realButton = *buttonTable;
  buttonTable++;
  return realButton;
}

void initTable(int table[]){
  buttonTable = table;
}

void initTime(int table[]){
  timeTable = table;
}

void setUp(void)
{
  readButton_StubWithCallback(fake_readButton);
  getTime_StubWithCallback(fake_getTime);
}

void tearDown(void)
{
}

//Create a button at the initial state
void test_createButton(void)
{ 
  int table[] = {IS_RELEASED};
  initTable(table);
  
  Button_t* btn = createButton();
  
  TEST_ASSERT_NOT_NULL(btn);
  TEST_ASSERT_EQUAL(IDLE, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(0, btn->recordedTime);
}

/**
 *
 *  Check if IDLE will remain at IDLE state
 *  if no IS_PRESSED event detected
 *
 */
void test_buttonFSM_maintain_in_IDLE_State(void)
{
  int table[] = {IS_RELEASED, IS_RELEASED};
  unsigned int time[] = {10};
  initTable(table);
  initTime(time);
  
  Button_t* btn = createButton();
  
  buttonFSM(btn);
  
  TEST_ASSERT_EQUAL(IDLE, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(0, btn->recordedTime);
}

/**
 *  Check if IDLE State can detect the PRESSED event
 *  and go to the WAIT State
 *
 */
void test_buttonFSM_IDLE_State_to_WAIT_State(void)
{
  int table[] = {IS_RELEASED, IS_PRESSED};
  unsigned int time[] = {10};
  initTable(table);
  initTime(time);
  
  Button_t* btn = createButton();
  
  buttonFSM(btn);
  
  TEST_ASSERT_EQUAL(WAIT, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(10, btn->recordedTime);
}

/**
 *
 *  Check if WAIT State can update the button->output
 *  if the previously detected changes was not a glitch
 *
 */
void test_buttonFSM_WAIT_State_update_output_if_really_changed(void)
{
  int table[] = {IS_RELEASED, IS_PRESSED, IS_PRESSED};
  unsigned int time[] = {10, 109, 110, 111};
  initTable(table);
  initTime(time);
  
  Button_t* btn = createButton();
  
  buttonFSM(btn); //Go to WAIT State
  TEST_ASSERT_EQUAL(WAIT, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(10, btn->recordedTime);
  
  buttonFSM(btn); //receive 99 not yet
  TEST_ASSERT_EQUAL(WAIT, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(10, btn->recordedTime);
  
  buttonFSM(btn);
  TEST_ASSERT_EQUAL(IDLE, btn->state);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->output);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->curState);
  TEST_ASSERT_EQUAL(10, btn->recordedTime);
}

/**
 *  
 *  Check if WAIT State can remain the previous button->output
 *  if the previous detected changes was a glitch
 *
 */
void test_buttonFSM_WAIT_State_output_no_change_if_just_once(void)
{
  int table[] = {IS_RELEASED, IS_PRESSED, IS_RELEASED};
  unsigned int time[] = {10, 109, 110, 111};
  initTable(table);
  initTime(time);
  
  Button_t* btn = createButton();
  
  buttonFSM(btn); //Go to WAIT State
  TEST_ASSERT_EQUAL(WAIT, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(10, btn->recordedTime);
  
  buttonFSM(btn); //receive 99 not yet
  TEST_ASSERT_EQUAL(WAIT, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(IS_PRESSED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(10, btn->recordedTime);
  
  buttonFSM(btn);
  TEST_ASSERT_EQUAL(IDLE, btn->state);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->output);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->prevState);
  TEST_ASSERT_EQUAL(IS_RELEASED, btn->curState);
  TEST_ASSERT_EQUAL(10, btn->recordedTime);
}

//=GetButton=====================================================================
void test_getButton_return_output(void)
{
  Button_t* btn = createButton();
  
  TEST_ASSERT_EQUAL(IS_RELEASED, getButton(btn));
}

