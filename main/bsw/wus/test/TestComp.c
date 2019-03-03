#include <stdint.h>
#include "../../os/System_Types.hpp"
#include "../../rte/commander/Commander.h"
#include "../../rte/commander/CommanderTypes.h"


#define instOn(Handler) On(Sys_ReturnType, Handler, TestComp)
CommanderInstance(Sys_ReturnType, TestComp);
RunnerInstance(Sys_ReturnType, TestComp);


//Commander
instOn(Init)
{
    Sys_ReturnType StatusL = SYS_OK;
     /*code*/
    printf("Init Test Comp\n");
    return StatusL;
}

instOn(StartUp)
{
    Sys_ReturnType StatusL = SYS_OK;
     /*code*/
    printf("StartUp Test Comp\n");
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
     /*code*/
     printf("Sleep Test Comp\n");
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
    printf("RUN Test Comp\n");
    return StatusL;
}

instOn(Write)
{
    Sys_ReturnType StatusL = SYS_OK;
     /*code*/
    return StatusL;
}

