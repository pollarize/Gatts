#include <stdint.h>
#include "../../os/System_Types.hpp"
#include "../../rte/commander/Commander.h"
#include "../../rte/commander/CommanderTypes.h"
#include "Wus_Cfg.h"

#include <stdio.h>

#define instOn(Handler) On(Sys_ReturnType, Handler, WUS)

CommanderInstance(Sys_ReturnType, WUS);
RunnerInstance(Sys_ReturnType, WUS);


typedef struct S_CommanderList{
    SCommanderPrototype** aList;
    const uint8_t u8SizeOfList;
    boolean bIsStartUp;
    uint16_t u16Timer;
    uint16_t u16DeadTimer;
}SCommanderList;

static SCommanderPrototype* CommanderList_BSW[] = 
{
    Commander_BSW_Components
};

static SCommanderList List_BSW =
{
    CommanderList_BSW, sizeof(CommanderList_BSW)/sizeof(CommanderList_BSW[0]),
    FALSE, 0, 0
};

static void InitList(SCommanderList* List);
static Sys_ReturnType Process_CommanderaList(SCommanderList*  List);

//Commander
instOn(Init)
{
    Sys_ReturnType StatusL = SYS_OK;
    InitList(&List_BSW);
    return StatusL;
}

instOn(StartUp)
{
    Sys_ReturnType StatusL = SYS_OK;
    InitList(&List_BSW);
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
    StatusL = Process_CommanderaList(&List_BSW);
    return StatusL;
}

instOn(Write)
{
    Sys_ReturnType StatusL = SYS_OK;
    /*code*/
    return StatusL;
}


static Sys_ReturnType Process_CommanderaList(SCommanderList* List)
{
    Sys_ReturnType StatusL = SYS_OK;
    if (List->bIsStartUp == FALSE)
    {
        if (SYS_OK == Commander_CheckAll(List->aList, List->u8SizeOfList, eCommanderState_Init) ||
            SYS_OK == Commander_CheckAll(List->aList, List->u8SizeOfList, eCommanderState_Sleep))
        {
            // Start UP all components
            StatusL = Commander_ExecuteAll(List->aList, List->u8SizeOfList, eCommanderState_StartUp);
            List->bIsStartUp = TRUE;
        }
        else
        {
            StatusL = Commander_ExecuteAll(List->aList, List->u8SizeOfList, eCommanderState_Init);
        }
    }
    else
    {
        // After startUp the components go to RUN phase automatically
        if (SYS_OK == Commander_CheckAll(List->aList, List->u8SizeOfList, eCommanderState_Run) ||
            cDEAD_ALIVE_Tasks == List->u16DeadTimer)
        {
            // Increment as Run Timer
            List->u16Timer++;
            printf("%d         \r",List->u16Timer);
            List->u16DeadTimer = 0;
        }
        else
        {
            if (SYS_OK == Commander_CheckAll(List->aList, List->u8SizeOfList, eCommanderState_Sleep) || 
                cDEAD_ALIVE_Tasks == List->u16DeadTimer)
            {
                // Increment as sleep timer
                List->u16Timer++;
                printf("%d         \r",List->u16Timer);
                List->u16DeadTimer = 0;

                // Timer is common for both WU and S
                if (List->u16Timer == cSLEEP_TIME_Tasks + cWAKEUP_TIME_Tasks)
                {
                    List->u16Timer = 0;
                    List->bIsStartUp = FALSE;
                }
            }
            else
            {
                // Increment dead timer
                List->u16DeadTimer++;
                printf("      %d\r",List->u16DeadTimer);
            }
        }
    }

    if (cWAKEUP_TIME_Tasks == List->u16Timer)
    {
        StatusL = Commander_ExecuteAll(List->aList, List->u8SizeOfList, eCommanderState_Sleep);
    }

    if (cDEAD_ALIVE_Tasks == List->u16DeadTimer)
    {
        printf("\nDead TIME Achieved! \n");
        StatusL = SYS_NOT_OK;
    }
    return StatusL;
}

static void InitList(SCommanderList* List)
{
    List->bIsStartUp = FALSE;
    List->u16Timer = 0;
    List->u16DeadTimer = 0;
}