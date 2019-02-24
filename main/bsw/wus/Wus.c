#include <stdint.h>
#include "../../os/System_Types.hpp"
#include "../../rte/commander/Commander.h"
#include "../../rte/commander/CommanderTypes.h"


#define instOn(Handler) On(Sys_ReturnType, Handler, WUS)

CommanderInstance(Sys_ReturnType, WUS);
RunnerInstance(Sys_ReturnType, WUS);


//Commander
instOn(Init)
{
    Sys_ReturnType StatusL = SYS_OK;
     /*code*/
    return StatusL;
}

instOn(StartUp)
{
    Sys_ReturnType StatusL = SYS_OK;
     /*code*/
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
    /*code*/
    return StatusL;
}

instOn(Write)
{
    Sys_ReturnType StatusL = SYS_OK;
     /*code*/
    return StatusL;
}

