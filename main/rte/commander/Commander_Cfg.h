
#define Commander_Import_Component(ComponentName) \
    extern SCommanderPrototype Commander_##ComponentName

#define Commander_Import_Row(ComponentName) \
    &Commander_##ComponentName

Commander_Import_Component(TestComp);
// Commander_Import_Component(WUS);

#define Commander_Components \
    Commander_Import_Row(TestComp),


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
