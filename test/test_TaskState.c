#include "unity.h"
#include "TaskState.h"
#include "LED_t.h"
#include "ErrorObject.h"
#include "mock_AllMock.h"
#include "Button_t.h"

int* btnTable = NULL;
unsigned int* timeTable = NULL;

unsigned int fake_getTime()
{
  unsigned int time = *timeTable;
  timeTable++;
  return time;
}

int fake_getButton(Button_t* btn)
{
  int status = *btnTable;
  btnTable++;
  return status;
}

void initBtnTable(int table[]) {
  btnTable = table;
}

void initTimeTable(int table[]) {
  timeTable = table;
}

void setUp(void)
{
  getTime_StubWithCallback(fake_getTime);
  getButton_StubWithCallback(fake_getButton);
}

void tearDown(void)
{
}

void test_createTaskState(void)
{ 
  Button_t* btn = createButton();
  LED_t* gLed   = createLED();
  TaskState* tState = createTaskState(250, gLed, btn);

  TEST_ASSERT_EQUAL(RELEASED, tState->state);
  TEST_ASSERT_EQUAL(0, tState->recordedTime);
  TEST_ASSERT_EQUAL(250, tState->interval);
  TEST_ASSERT_EQUAL_PTR(gLed, tState->whichLED);
  TEST_ASSERT_EQUAL_PTR(btn, tState->whichButton);
  TEST_ASSERT_EQUAL(TRUE, tState->buttonReleased);
}
//=RELEASED State==============================================================================
/**************************************************************
  This test make sure the buttonAndLED function will only turn
  the LED ON when the button IS_PRESSED
 **************************************************************/
void test_buttonAndLED_RELEASED_State(void)
{
  int table[] = { IS_RELEASED, IS_PRESSED};
  int timeTable[] = {0, 10};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  //End of Initialization

  
  buttonAndLED(tState);
  TEST_ASSERT_FALSE(tState->whichLED->ledState);
  TEST_ASSERT_EQUAL(RELEASED, tState->state);
  TEST_ASSERT_EQUAL(0, tState->recordedTime);
  
  buttonAndLED(tState);
  TEST_ASSERT_TRUE(tState->whichLED->ledState);
  TEST_ASSERT_EQUAL(PRESSED_ON, tState->state);
  TEST_ASSERT_EQUAL(250, tState->interval);
  TEST_ASSERT_EQUAL(0, tState->recordedTime);
}
//=PRESSED_ON State=========================================================================
/**************************************************************
  This test make sure the buttonAndLED function will goto
  RELEASED_ON state when button is released
  
  Also, the recordedTime shall not be changed
 **************************************************************/
void test_buttonAndLED_PRESSED_ON_State_change_the_guard_buttonReleased_to_TRUE(void)
{
  int table[] = {IS_PRESSED,IS_PRESSED,IS_RELEASED};
  int timeTable[] = {0, 10};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  buttonAndLED(tState); //GO TO PRESSED_ON State
  //End of Initialization
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_ON, tState->state);
  TEST_ASSERT_EQUAL(0, tState->recordedTime);
  TEST_ASSERT_EQUAL(FALSE, tState->buttonReleased);
  
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_ON, tState->state);
  TEST_ASSERT_EQUAL(0, tState->recordedTime);
  TEST_ASSERT_EQUAL(TRUE, tState->buttonReleased);
}

/**************************************************************
  This test tested transition from PRESSED_ON to PRESSED_OFF
  when timer expired
 **************************************************************/
void test_buttonAndLED_PRESSED_ON_State_to_PRESSED_OFF(void)
{
  int table[] = {IS_PRESSED, IS_PRESSED, IS_PRESSED, IS_PRESSED};
  int timeTable[] = {0, 10, 249, 250, 252};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  buttonAndLED(tState); //GO TO PRESSED_ON State
  //End of Initialization
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_ON, tState->state);

  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_ON, tState->state);
  
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_OFF, tState->state);
  TEST_ASSERT_FALSE(tState->whichLED->ledState);
  TEST_ASSERT_EQUAL(252, tState->recordedTime);
}
/**************************************************************
  This test make sure the buttonAndLED function will goto
  TURNING_OFF state when button is pressed AGAIN at PRESSED_ON
  State. Also test whether led is off
 **************************************************************/
void test_buttonAndLED_PRESSED_ON_State_to_TURNING_OFF_State(void)
{
  int table[] = {IS_PRESSED, IS_RELEASED,IS_PRESSED};
  int timeTable[] = {0, 10, 15};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  buttonAndLED(tState); //GO TO PRESSED_ON State
  //End of Initialization
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_ON, tState->state);
  TEST_ASSERT_EQUAL(0, tState->recordedTime);
  TEST_ASSERT_EQUAL(TRUE, tState->buttonReleased);
  
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(TURNING_OFF, tState->state);
  TEST_ASSERT_FALSE(tState->whichLED->ledState);
  TEST_ASSERT_EQUAL(0, tState->recordedTime);
  TEST_ASSERT_EQUAL(FALSE, tState->buttonReleased);
}

//=PRESSED_OFF State================================================================
/**************************************************************
  This test make sure the buttonAndLED function will goto
  PRESSED_ON state when timer expired during PRESSED_OFF
  State
 **************************************************************/
void test_buttonAndLED_PRESSED_OFF_State_to_PRESSED_ON_State(void)
{
  int table[] = {IS_PRESSED, IS_PRESSED, IS_PRESSED, IS_PRESSED};
  int timeTable[] = {0, 249, 250, 251};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  tState->state = PRESSED_OFF;
  tState->buttonReleased = FALSE;
  //End of Initialization
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_OFF, tState->state);

  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_OFF, tState->state);
  
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_ON, tState->state);
  TEST_ASSERT_TRUE(tState->whichLED->ledState);
  TEST_ASSERT_EQUAL(251, tState->recordedTime);
}

/**************************************************************
  This test make sure the buttonAndLED function will change
  guard (buttonReleased) to TRUE when button IS_RELEASED during 
  PRESSED_OFF State
 **************************************************************/
void test_buttonAndLED_PRESSED_OFF_State_to_change_guard_buttonReleased_to_TRUE(void)
{
  int table[] = {IS_PRESSED, IS_RELEASED};
  int timeTable[] = {0, 249, 250};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  tState->state = PRESSED_OFF;
  tState->buttonReleased = FALSE;
  //End of Initialization
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_OFF, tState->state);
  TEST_ASSERT_FALSE(tState->buttonReleased);

  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_OFF, tState->state);
  TEST_ASSERT_TRUE(tState->buttonReleased);
}


/**************************************************************
  This test make sure the buttonAndLED function will goto
  TURNING_OFF state when button IS_PRESSED after release during 
  PRESSED_OFF State
 **************************************************************/
void test_buttonAndLED_PRESSED_OFF_State_to_TURNING_OFF_State(void)
{
  int table[] = {IS_RELEASED, IS_PRESSED};
  int timeTable[] = {0, 249, 250};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  tState->state = PRESSED_OFF;
  tState->buttonReleased = FALSE;
  
  //End of Initialization
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(PRESSED_OFF, tState->state);
  TEST_ASSERT_TRUE(tState->buttonReleased);
  
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(TURNING_OFF, tState->state);
  TEST_ASSERT_FALSE(tState->whichLED->ledState);
  TEST_ASSERT_FALSE(tState->buttonReleased);
}
//=TURNING_OFF State=============================================================
/**************************************************************
  This test make sure the buttonAndLED function will goto
  RELEASED state when button IS_RELEASED during TURNING_OFF
  State
 **************************************************************/
void test_buttonAndLED_TURNING_OFF_State_to_RELEASED_State(void)
{
  int table[] = {IS_PRESSED, IS_RELEASED};
  int timeTable[] = {0, 249, 250};
  
  initBtnTable(table);
  initTimeTable(timeTable);
  
  TaskState* tState = createTaskState(250, createLED(), createButton());
  tState->state = TURNING_OFF;
  tState->buttonReleased = FALSE;
  //End of Initialization
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(TURNING_OFF, tState->state);
  TEST_ASSERT_FALSE(tState->buttonReleased);
  
  buttonAndLED(tState);
  TEST_ASSERT_EQUAL(RELEASED, tState->state);
  TEST_ASSERT_TRUE(tState->buttonReleased);
}