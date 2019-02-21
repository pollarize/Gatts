#include "CommanderTypes.h"

#define CommanderInstance(ReturnType, ComponentName)  \
    static ReturnType OnInit_##ComponentName();       \
    static ReturnType OnStartUp_##ComponentName();    \
    static ReturnType OnRun_##ComponentName();        \
    static ReturnType OnSleep_##ComponentName();      \
    static ReturnType OnDeInit_##ComponentName();     \
    SCommanderPrototype Commander_##ComponentName = { \
        eCommanderState_Undefined,                    \
        eCommanderState_Undefined,                    \
        {&OnInit_##ComponentName,                     \
         &OnStartUp_##ComponentName,                  \
         &OnRun_##ComponentName,                      \
         &OnSleep_##ComponentName,                    \
         &OnDeInit_##ComponentName}}

#define RunnerInstance(ReturnType, ComponentName)  \
    static ReturnType OnRead_##ComponentName();    \
    static ReturnType OnProcess_##ComponentName(); \
    static ReturnType OnWrite_##ComponentName();   \
    SRunnerPrototype Runner_##ComponentName = {    \
        eRunnerState_Undefined,                    \
        {&OnRead_##ComponentName,                  \
         &OnProcess_##ComponentName,               \
         &OnWrite_##ComponentName}}

#define On(ReturnType, Handler, ComponentName) \
    static ReturnType On##Handler##_##ComponentName()

// Exported functions  
extern Sys_ReturnType Commander_SendCommand(SCommanderPrototype *Commander, ECommand_Type Command);
extern Sys_ReturnType Component_Main(SCommanderPrototype *Commander);
extern Sys_ReturnType Commander_Execute(EExecContext Context, SCommanderPrototype *Commander, ECommand_Type Command);
extern Sys_ReturnType Commander_Run(SRunnerPrototype *Runner);
extern Sys_ReturnType Commander_ExecuteAll(ECommand_Type Command);
extern Sys_ReturnType Commander_StateUpdater(SCommanderPrototype *Commander);