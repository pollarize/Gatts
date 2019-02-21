
#define Commander_Import_Component(ComponentName) \
    extern SCommanderPrototype Commander_##ComponentName

#define Commander_Import_Row(ComponentName) \
    &Commander_##ComponentName



Commander_Import_Component(TestComp);

#define Commander_Components \
    Commander_Import_Row(TestComp),\
    Commander_Import_Row(TestComp),\
    Commander_Import_Row(TestComp),\
    Commander_Import_Row(TestComp),\
    Commander_Import_Row(TestComp),

#define Commander_DisAllowed_Transitions \
    {eCommanderState_Sleep, eCommanderState_Run},  \
    {eCommanderState_DeInit, eCommanderState_Run}, \
    {eCommanderState_Init, eCommanderState_Run},   
