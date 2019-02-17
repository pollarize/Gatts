/*
 * Os.c
 *
 *  Created on: Sep 17, 2017
 *      Author: Mihail Maldzhanski
 */

//-----------------------------------------------------------------------------------------
//General Includes
//-----------------------------------------------------------------------------------------
#include "System_Types.hpp"
#include "System_config.hpp"
#include "Os_config.hpp"

//-----------------------------------------------------------------------------------------
//General Defines
//-----------------------------------------------------------------------------------------
#define Task(Data,Time,StackSize)  Task ## Data( void *pvParameters );                       \
/*Define body of the function for every task*/                                               \
void static Task ## Data(void *pvParameters)                                                 \
{                                                                                            \
  sTaskParameter* TaskParamL =  (sTaskParameter*) pvParameters;                              \
  TaskParamL->TaskInitFunction();                                                            \
  for (;;)                                                                                   \
  {                                                                                          \
    TaskParamL->TaskExecutionFunction();                                                     \
    vTaskDelay( TaskParamL->u16TaskTime / portTICK_PERIOD_MS );                              \
  }                                                                                          \
}                                                                                            \
/*Define outer Main & Init Functions for specific task*/                                     \
extern void Task ## Data ##_MainFunction( void );                                            \
extern void Task ## Data ##_InitFunction( void );                                            \
static sTaskParameter TaskPrameters ## Data ## L = {&Task ## Data ##_InitFunction,           \
                                             &Task ## Data ##_MainFunction, (Time)};         \
/* Structure that will hold the TCB of the task being created.*/                             \
static StaticTask_t xTaskBuffer ## Data ## L;                                                \
                                                                                             \
/* Buffer that the task being created will use as its stack.  Note this is*/                 \
/* an array of StackType_t variables.  The size of StackType_t is dependent on*/             \
/* the RTOS port.*/                                                                          \
static StackType_t xStack ## Data ## L[(StackSize)] 


#define TaskOptionsSet(TaskName,TaskName_Char, StackSize, Priority)                          \
/*Set Up tasks*/                                                                             \
        xTaskCreate(                                                                         \
        Task##TaskName,                           /*Related function*/                       \
        (const portCHAR *)TaskName_Char,          /*Name*/                                   \
        (StackSize),                              /*Stack size (in words)*/                  \
        &TaskPrameters ## TaskName ## L ,         /*Parameter (sTaskParameter)*/             \
        (Priority),                               /*Priority*/                               \
        NULL);                                    /*Handle (pointer to handle ID)*/


#define TaskStaticOptionsSet(TaskName,TaskName_Char, StackSize, Priority)                          \
/*Set Up tasks*/                                                                                   \
        xTaskCreateStatic(                                                                         \
        Task##TaskName,                            /* Function that implements the task.*/         \
        TaskName_Char,                             /* Text name for the task.*/                    \
        (StackSize),                               /* Stack size in bytes, not words.*/            \
        &TaskPrameters ## TaskName ## L,           /* Parameter passed into the task.*/            \
        (Priority),                                /* Priority at which the task is created.*/     \
        xStack ## TaskName ## L,                   /* Array to use as the task's stack.*/          \
        &xTaskBuffer ## TaskName ## L)             /* Variable to hold the task's data structure.*/

//-----------------------------------------------------------------------------------------
//General Types
//-----------------------------------------------------------------------------------------
typedef struct{
    void     (*TaskInitFunction) ( void );
    void     (*TaskExecutionFunction) ( void );
    uint16_t u16TaskTime;
}sTaskParameter;

//-----------------------------------------------------------------------------------------
//General Static Data
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Exported Data
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
//General Static Function Prototypes
//-----------------------------------------------------------------------------------------
void static Task(Task_15ms, OS_TASK_MIN_TIME, OS_TASK_MIN_WORDS);
void static Task(Task_45ms, OS_TASK_AVG_TIME, OS_TASK_MIN_WORDS);
void static Task(Task_105ms, OS_TASK_MAX_TIME, OS_TASK_MIN_WORDS);
void static Task(Task_990ms, OS_TASK_EXTENDED_TIME, OS_TASK_MIN_WORDS);

//-----------------------------------------------------------------------------------------
//General Exported Function Prototypes
//-----------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------
// void System_Loop_Stub() { /*FreeRTOS manages loop for every task*/ }
//-----------------------------------------------------------------------------------------

void Os_Tasks_Init()
{
    //-------------------------------------------------------------------------------------
    TaskStaticOptionsSet(Task_15ms,"Task_15ms",OS_TASK_MIN_WORDS,OS_TASK_PRIORITY_HIGH);
    //-------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------
    TaskStaticOptionsSet(Task_45ms,"Task_45ms",OS_TASK_MIN_WORDS,OS_TASK_PRIORITY_MEDIUM);
    //-------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------
    TaskStaticOptionsSet(Task_105ms,"Task_105ms",OS_TASK_MIN_WORDS,OS_TASK_PRIORITY_MEDIUM);
    //-------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------
    TaskStaticOptionsSet(Task_990ms,"Task_990ms",OS_TASK_MIN_WORDS,OS_TASK_PRIORITY_LOW);
    //-------------------------------------------------------------------------------------
}

//-----------------------------------------------------------------------------------------
//General Static Functions
//-----------------------------------------------------------------------------------------

