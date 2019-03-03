#include <stdint.h>
#include "../../os/System_Types.hpp"
#include "../../rte/commander/Commander.h"
#include "../../rte/commander/CommanderTypes.h"

#define instOn(Handler) On(Sys_ReturnType, Handler, WUS)

CommanderInstance(Sys_ReturnType, WUS);
RunnerInstance(Sys_ReturnType, WUS);

static boolean bIsStartUp = FALSE;
static uint8_t u8Timer = 0;

//Commander
instOn(Init)
{
    Sys_ReturnType StatusL = SYS_OK;
    bIsStartUp = FALSE;
    u8Timer = 0;
    return StatusL;
}

instOn(StartUp)
{
    Sys_ReturnType StatusL = SYS_OK;
    bIsStartUp = FALSE;
    u8Timer = 0;
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
        if (SYS_OK == Commander_CheckAll(eCommanderState_Run))
        {
            u8Timer++;
        }
        else
        {
            if (SYS_OK == Commander_CheckAll(eCommanderState_Sleep))
            {
                u8Timer = 0;
                bIsStartUp = FALSE;
            }
        }
    }

    if (u8Timer == 4)
    {
        StatusL = Commander_ExecuteAll(eCommanderState_Sleep);
    }

    return StatusL;
}

instOn(Write)
{
    Sys_ReturnType StatusL = SYS_OK;
    /*code*/
    return StatusL;
}
