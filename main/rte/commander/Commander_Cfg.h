
#define Commander_DisAllowed_Transitions \
    {eCommanderState_Sleep, eCommanderState_Run},  \
    {eCommanderState_DeInit, eCommanderState_Run}, \
    {eCommanderState_Init, eCommanderState_Run}, \
    {eCommanderState_Run, eCommanderState_StartUp},  \
    {eCommanderState_Run, eCommanderState_Init},  \
    {eCommanderState_Run, eCommanderState_DeInit},  \
    {eCommanderState_Run, eCommanderState_Undefined},  \
    {eCommanderState_Undefined, eCommanderState_Sleep},  \
    {eCommanderState_Undefined, eCommanderState_Run},  \
    {eCommanderState_Undefined, eCommanderState_StartUp},  \
    {eCommanderState_Undefined, eCommanderState_DeInit}
