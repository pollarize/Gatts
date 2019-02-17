
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
