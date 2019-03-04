#include <stdint.h>
#include "../../os/System_Types.hpp"
#include "CommanderTypes.h"
#include "Commander.h"
#include "Commander_Cfg.h"

static SDisAllowed_Commander_Transitions CommanderDATrans[] = {
    Commander_DisAllowed_Transitions};

//-----------------------------------------------------------------------------------------
// Function Bodies
//-----------------------------------------------------------------------------------------
static boolean IsTransitionAllowed(ECommander_States CurrentP, ECommander_States NextP)
{
    boolean isAllowed = TRUE;
    uint8_t u8CounterL = 0;

    for (u8CounterL = 0; u8CounterL < sizeof(CommanderDATrans) / sizeof(CommanderDATrans[0]); u8CounterL++)
    {
        if (CurrentP == CommanderDATrans[u8CounterL].Current &&
            NextP == CommanderDATrans[u8CounterL].Next)
        {
            isAllowed = FALSE;
        }
    }

    return isAllowed;
}

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

    if (Runner->CurrentState >= eRunnerState_Count)
    {
        Runner->CurrentState = eRunnerState_Read;
    }

    while (Runner->CurrentState < eRunnerState_Count)
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

Sys_ReturnType Commander_Execute(EExecContext Context, SCommanderPrototype *Commander, ECommander_States Command)
{
    Sys_ReturnType StatusL = SYS_OK;
    boolean isTransiotionAllowedL;
 
    if (Context == eExecContext_External)
    {
        isTransiotionAllowedL = IsTransitionAllowed(Commander->CurrentState, Command);
        if (FALSE != isTransiotionAllowedL)
        {
            Commander->RequestedState = Command;
        }
        else
        {
            StatusL = SYS_NOT_OK;
        }
    }
        
    if (Context == eExecContext_Internal)
    {
        isTransiotionAllowedL = IsTransitionAllowed(Commander->CurrentState, Commander->RequestedState);
        if (FALSE != isTransiotionAllowedL)
        {
            StatusL = Commander_StateUpdater(Commander);
        }
        else
        {
            StatusL = SYS_NOT_OK;
        }
    }
   
    return StatusL;
}

Sys_ReturnType Commander_ExecuteAll(SCommanderPrototype** CommanderList, uint8_t u8SizeOfList ,ECommander_States Command)
{
    uint8_t u8CounterL = 0;
    Sys_ReturnType StatusL = SYS_OK;
    for (u8CounterL = 0; u8CounterL < u8SizeOfList; u8CounterL++)
    {
        StatusL |= Commander_Execute(eExecContext_External, CommanderList[u8CounterL], Command);
    }
    return StatusL;
}


Sys_ReturnType Commander_StateUpdater(SCommanderPrototype *Commander)
{
    Sys_ReturnType StatusL = SYS_OK;
    if (Commander->CurrentState != Commander->RequestedState || 
        Commander->CurrentState == eCommanderState_Run)
    {
        StatusL = Execute(eCommandType_Commander, (uint32_t *)&Commander->Handlers, (uint8_t)Commander->RequestedState);
        if (StatusL == SYS_OK)
        {
            Commander->CurrentState = Commander->RequestedState;
            if(Commander->CurrentState == eCommanderState_StartUp){
                Commander->RequestedState = eCommanderState_Run;
            } 
        }
    }
    else
    {
        StatusL = SYS_NOT_OK;
    }
    return StatusL;
}

Sys_ReturnType Commander_SendCommand(SCommanderPrototype *Commander, ECommander_States Command)
{
    Sys_ReturnType StatusL = SYS_OK;
    StatusL = Commander_Execute(eExecContext_External, Commander, Command);
    return StatusL;
}

Sys_ReturnType Commander_CheckAll(SCommanderPrototype **CommanderList, uint8_t u8SizeOfList ,ECommander_States Command)
{
    uint8_t u8CounterL = 0;
    Sys_ReturnType StatusL = SYS_OK;
    for (u8CounterL = 0; u8CounterL < u8SizeOfList; u8CounterL++)
    {
        StatusL |= (Sys_ReturnType)(CommanderList[u8CounterL]->CurrentState != Command);
    }

    if (StatusL != SYS_OK)
    {
        StatusL = SYS_PENDING;
    }

    return StatusL;
}

Sys_ReturnType Component_Main(SCommanderPrototype *Commander)
{
    Sys_ReturnType StatusL = SYS_OK;
    StatusL = Commander_Execute(eExecContext_Internal , Commander, eCommanderState_Run);
    return StatusL;
}

Sys_ReturnType Component_AutoStartUp(SCommanderPrototype *Commander)
{
    Sys_ReturnType StatusL = SYS_OK;

    // Init component
    StatusL = Commander_SendCommand(Commander, eCommanderState_Init);
    StatusL |= Commander_Execute(eExecContext_Internal , Commander, eCommanderState_Init);

    //StartUp Component
    StatusL |= Commander_SendCommand(Commander, eCommanderState_StartUp);
    StatusL |= Commander_Execute(eExecContext_Internal , Commander, eCommanderState_StartUp);

    return StatusL;
}