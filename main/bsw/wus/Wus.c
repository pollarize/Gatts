#include <stdint.h>
#include "../../os/System_Types.hpp"
#include "../../rte/commander/Commander.h"
#include "../../rte/commander/CommanderTypes.h"
#include "Wus_Cfg.h"

#define instOn(Handler) On(Sys_ReturnType, Handler, WUS)

CommanderInstance(Sys_ReturnType, WUS);
RunnerInstance(Sys_ReturnType, WUS);

static boolean bIsStartUp = FALSE;
static uint16_t u16Timer = 0;
static uint16_t u16DeadTimer = 0;

//Commander
instOn(Init)
{
    Sys_ReturnType StatusL = SYS_OK;
    bIsStartUp = FALSE;
    u16Timer = 0;
    u16DeadTimer = 0;
    return StatusL;
}

instOn(StartUp)
{
    Sys_ReturnType StatusL = SYS_OK;
    bIsStartUp = FALSE;
    u16Timer = 0;
    u16DeadTimer = 0;
    return StatusL;
}

instOn(Run)
{
    Sys_ReturnType StatusL = SYS_OK;
    StatusL = Commander_Run(&Runner_WUS);
    return StatusL;
}

instOn(Sleep)
{
    Sys_ReturnType StatusL = SYS_OK;
    /*code*/
    return StatusL;
}

instOn(DeInit)
{
    Sys_ReturnType StatusL = SYS_OK;
    /*code*/
    return StatusL;
}

// Runner
instOn(Read)
{
    Sys_ReturnType StatusL = SYS_OK;
    /*code*/
    return StatusL;
}

instOn(Process)
{
    Sys_ReturnType StatusL = SYS_OK;
    if (bIsStartUp == FALSE)
    {
        if (SYS_OK == Commander_CheckAll(eCommanderState_Init) ||
            SYS_OK == Commander_CheckAll(eCommanderState_Sleep))
        {
            // Start UP all components
            StatusL = Commander_ExecuteAll(eCommanderState_StartUp);
            bIsStartUp = TRUE;
        }
    }
    else
    {
        // After startUp the components go to RUN phase automatically
        if (SYS_OK == Commander_CheckAll(eCommanderState_Run) ||
            cDEAD_ALIVE_Tasks == u16DeadTimer)
        {
            // Increment as Run Timer
            u16Timer++;
            printf("%d         \r",u16Timer);
            u16DeadTimer = 0;
        }
        else
        {
            if (SYS_OK == Commander_CheckAll(eCommanderState_Sleep) || 
                cDEAD_ALIVE_Tasks == u16DeadTimer)
            {
                // Increment as sleep timer
                u16Timer++;
                printf("%d         \r",u16Timer);
                u16DeadTimer = 0;

                // Timer is common for both WU and S
                if (u16Timer == cSLEEP_TIME_Tasks + cWAKEUP_TIME_Tasks)
                {
                    u16Timer = 0;
                    bIsStartUp = FALSE;
                }
            }
            else
            {
                // Increment dead timer
                u16DeadTimer++;
                printf("      %d\r",u16DeadTimer);
            }
        }
    }

    if (cWAKEUP_TIME_Tasks == u16Timer)
    {
        StatusL = Commander_ExecuteAll(eCommanderState_Sleep);
    }

    if (cDEAD_ALIVE_Tasks == u16DeadTimer)
    {
        printf("\nDead TIME Achieved! \n");
    }

    return StatusL;
}

instOn(Write)
{
    Sys_ReturnType StatusL = SYS_OK;
    /*code*/
    return StatusL;
}
