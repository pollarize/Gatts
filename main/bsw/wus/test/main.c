#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <windows.h>

#include "../../../os/System_Types.hpp"
#include "../../../rte/commander/Commander.h"
#include "../../../rte/commander/CommanderTypes.h"

extern SCommanderPrototype Commander_WUS;
extern SCommanderPrototype Commander_TestComp;

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

void SetInterval(clock_t *before, pFunction callback, uint32_t timeMs)
{
    clock_t diff = clock() - *before;
    uint32_t diffMs = diff * 1000/CLOCKS_PER_SEC;
    if ( diffMs >= timeMs )
    {
        callback();
        // printf("%d ",diffMs );
        if(diffMs > timeMs){
            diff -= (diffMs - timeMs)/1000*CLOCKS_PER_SEC;
        }

        *before += diff;
    }
}

void Task_1000ms()
{
    Component_Main(&Commander_WUS);
} 

void Task_2000ms()
{
    Component_Main(&Commander_TestComp);
} 

void Task_5000ms()
{
    
} 

int main()
{
    clock_t before[] = {clock(),clock(),clock()};

    // Commander_SendCommand(&Commander_WUS, eCommanderState_Init);
    Component_AutoStartUp(&Commander_WUS);
    // Commander_ExecuteAll(eCommanderState_Init);

    while(1)
    {
        uint8_t i = 0;
        SetInterval(&before[i++],(pFunction )&Task_1000ms,100);
        SetInterval(&before[i++],(pFunction )&Task_2000ms,100);
        // SetInterval(&before[i++],(pFunction )&Task_5000ms,5000);
        Sleep(1);
    }

    return 0;
}
