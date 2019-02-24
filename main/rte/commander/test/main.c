#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>

#include "../../../os/System_Types.hpp"
#include "Commander.h"
#include "CommanderTypes.h"


#define instOn(Handler) On(Sys_ReturnType, Handler, TestComp)

const char* StatusStr[]={
    "OK",
    "NOK",
    "PENDING"
};

const char* CommandStr[] = {
   "Undefined",
   "Init",
   "StartUp",
   "Run",
   "Sleep",
   "DeInit"
};

CommanderInstance(Sys_ReturnType, TestComp);
RunnerInstance(Sys_ReturnType, TestComp);

#define Commander_SendCommand(who, what) \
    Sys_ReturnType StatusL = Commander_SendCommand((who), (what));\
    printf("\nCommand = %s - %s\n",CommandStr[(what)],StatusStr[StatusL])


#define Component_Main(who) \
    Sys_ReturnType StatusL = Component_Main((who));\
    printf("\Run = %s\n",StatusStr[StatusL])


//Commander
instOn(Init)
{
    Sys_ReturnType StatusL = SYS_OK;
    printf("Init\n");
    return StatusL;
}

instOn(StartUp)
{
    Sys_ReturnType StatusL = SYS_OK;
    printf("StartUp\n");
    return StatusL;
}

instOn(Run)
{
    Sys_ReturnType StatusL = SYS_OK;
    StatusL = Commander_Run(&Runner_TestComp);
    return StatusL;
}

instOn(Sleep)
{
    Sys_ReturnType StatusL = SYS_OK;
    printf("Sleep\n");
    return StatusL;
}

instOn(DeInit)
{
    Sys_ReturnType StatusL = SYS_OK;
    return StatusL;
}

// Runner
instOn(Read)
{
    Sys_ReturnType StatusL = SYS_OK;
    return StatusL;
}

instOn(Process)
{
    Sys_ReturnType StatusL = SYS_OK;
    printf("Hello\n");
    return StatusL;
}

instOn(Write)
{
    Sys_ReturnType StatusL = SYS_OK;
    return StatusL;
}


void SetInterval(clock_t *before, pFunction callback, uint32_t timeMs)
{
    clock_t diff = clock() - *before;
    uint32_t diffMs = diff * 1000/CLOCKS_PER_SEC;
    if ( diffMs >= timeMs )
    {
        callback();
        printf("%d ",diffMs );
        if(diffMs > timeMs){
            diff -= (diffMs - timeMs)/1000*CLOCKS_PER_SEC;
        }

        *before += diff;
    }
}

void Task_1000ms()
{
    Component_Main(&Commander_TestComp);
} 

void Task_2000ms()
{
    Commander_SendCommand(&Commander_TestComp, eCommanderState_StartUp);
} 

void Task_5000ms()
{
    Commander_SendCommand(&Commander_TestComp, eCommanderState_Sleep);
} 

int main()
{
    clock_t before[] = {clock(),clock(),clock()};

    Commander_SendCommand(&Commander_TestComp, eCommanderState_Init);
    // Commander_Execute(eExecContext_External,&Commander_TestComp, eCommanderState_Run);
    // Commander_ExecuteAll(eCommanderState_Run);

    while(1)
    {
        uint8_t i = 0;
        SetInterval(&before[i++],(pFunction )&Task_1000ms,1000);
        SetInterval(&before[i++],(pFunction )&Task_2000ms,10000);
        SetInterval(&before[i++],(pFunction )&Task_5000ms,20000);
        Sleep(1);
    }

    return 0;
}
