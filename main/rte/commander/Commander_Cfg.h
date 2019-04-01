
#define Commander_Allowed_Transitions                   \
    {eCommanderState_Undefined, eCommanderState_Init},  \
    {eCommanderState_DeInit, eCommanderState_Init},     \
    {eCommanderState_Init, eCommanderState_StartUp},    \
    {eCommanderState_StartUp, eCommanderState_Run},     \
    {eCommanderState_Run, eCommanderState_Run},         \
    {eCommanderState_Run, eCommanderState_Sleep},       \
    {eCommanderState_Sleep, eCommanderState_StartUp},   \
    {eCommanderState_Sleep, eCommanderState_DeInit} 
