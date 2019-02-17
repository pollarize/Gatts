#include <stdint.h>
#include "../../os/System_Types.hpp"
#include "CommanderTypes.h"
#include "Commander.h"
#include "Commander_Cfg.h"

static SCommanderPrototype *CommanderList[] = {
    Commander_Components};

//-----------------------------------------------------------------------------------------
// Function Bodies
//-----------------------------------------------------------------------------------------
static Sys_ReturnType Execute(ECommand_Type Type, uint32_t *Handlers, uint8_t Command)
{
    uint32_t u32AddrL = (uint32_t)Handlers;
    pFunction Handler = NULL;
    Sys_ReturnType StatusL = SYS_OK;

    switch (Type)
    {
    case eCommandType_Commander:
        if (eCommanderState_Undefined < Command && eCommanderState_Count > Command)
        {
            u32AddrL = (u32AddrL + ((Command - 1) * sizeof(Handlers)));
        }
        break;
    case eCommandType_Runner:
        if (eRunnerState_Undefined < Command && eRunnerState_Count > Command)
        {
            u32AddrL = (u32AddrL + ((Command - 1) * sizeof(Handlers)));
        }
        break;
    default:
        StatusL = SYS_NOT_OK;
        break;
    }

    //Get Function handler
    Handler = (void *)*(uint32_t *)u32AddrL;

    if (Handler != NULL)
    {
        StatusL = Handler();
    }
    else
    {
        StatusL = SYS_NOT_OK;
    }

    return StatusL;
}

Sys_ReturnType Commander_Run(SRunnerPrototype *Runner)
{
    Sys_ReturnType StatusL = SYS_OK;

    if ( Runner->CurrentState >= eRunnerState_Count){
        Runner->CurrentState = eRunnerState_Read;
    }

    while(Runner->CurrentState < eRunnerState_Count)
    {
        StatusL |= Execute(eCommandType_Runner, (uint32_t *)&Runner->Handlers, (uint8_t)Runner->CurrentState);
#ifdef RUNNER_SYNC
        if (Status == SYS_OK)
#endif // RUNNER_SYNC
        {
             Runner->CurrentState++;
        }
    }
    return StatusL;
}

Sys_ReturnType Commander_Execute(SCommanderPrototype *Commander, ECommand_Type Command)
{
    Sys_ReturnType StatusL = SYS_OK;
    StatusL = Execute(eCommandType_Commander, (uint32_t *)&Commander->Handlers, (uint8_t)Command);
    if (StatusL == SYS_OK)
    {
        Commander->CurrentState = Command;
    }
    return StatusL;
}

Sys_ReturnType Commander_ExecuteAll(ECommand_Type Command)
{
    uint8_t u8CounterL = 0;
    Sys_ReturnType StatusL = SYS_OK;
    for (u8CounterL = 0; u8CounterL < sizeof(CommanderList) / sizeof(CommanderList[0]); u8CounterL++)
    {
        StatusL |= Commander_Execute(CommanderList[u8CounterL], Command);
    }
    return StatusL;
}
