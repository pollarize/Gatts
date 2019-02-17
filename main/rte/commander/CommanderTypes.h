#ifndef GeneralType
#define GeneralType

typedef Sys_ReturnType (*pFunction)(void);

typedef enum E_Commander_States{
    eCommanderState_Undefined,
    eCommanderState_Init,
    eCommanderState_StartUp,
    eCommanderState_Run,
    eCommanderState_Sleep,
    eCommanderState_DeInit,
    eCommanderState_Count
}ECommander_States;

typedef enum E_Runner_States{
    eRunnerState_Undefined,
    eRunnerState_Read,
    eRunnerState_Process,
    eRunnerState_Write,
    eRunnerState_Count
}ERunner_States;

typedef struct S_Commander_Handler{
    pFunction OnInit;
    pFunction OnStartUp;
    pFunction OnRun;
    pFunction OnSleep;
    pFunction OnDeInit;
}SCommander_Handler;

typedef struct S_Runner_Handler{
    pFunction OnRead;
    pFunction OnProcess;
    pFunction OnWrite;
}SRunner_Handler;

typedef struct S_CommanderPrototype{
    ECommander_States CurrentState;
    SCommander_Handler Handlers;
}SCommanderPrototype;

typedef struct SRunnerPrototype{
    ERunner_States CurrentState;
    SRunner_Handler Handlers;
}SRunnerPrototype;

typedef enum E_Command_Type{
    eCommandType_Commander,
    eCommandType_Runner,
    eCommandType_Count
}ECommand_Type;

#endif