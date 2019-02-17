#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "../../../os/System_Types.hpp"
#include "CommanderTypes.h"
#include "Commander.h"

#define instOn(Handler) On(Sys_ReturnType, Handler, TestComp)

CommanderInstance(Sys_ReturnType, TestComp);
RunnerInstance(Sys_ReturnType, TestComp);

//Commander
instOn(Init)
{
    Sys_ReturnType StatusL = SYS_OK;
    return StatusL;
}

instOn(StartUp)
{
    Sys_ReturnType StatusL = SYS_OK;
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
    Sys_ReturnType StatusL = SYS_NOT_OK;
    return StatusL;
}

instOn(Write)
{
    Sys_ReturnType StatusL = SYS_OK;
    return StatusL;
}

int main()
{
    Commander_Execute(&Commander_TestComp, eCommanderState_Init);
    Commander_Execute(&Commander_TestComp, eCommanderState_Run);
    Commander_ExecuteAll(eCommanderState_Run);
    return 0;
}
