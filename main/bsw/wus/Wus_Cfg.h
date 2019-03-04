#ifndef WUS_CFG_H
#define WUS_CFG_H

#define cTaskTime    ((uint16_t) 100)  //ms

#define cWAKEUP_TIME_s ((uint16_t) 3)    //seconds
#define cSLEEP_TIME_s  ((uint16_t) 10)   //seconds
#define cDEAD_ALIVE_ms ((uint16_t) 1500) // ms

#define cWAKEUP_TIME_Tasks  ((uint16_t) (cWAKEUP_TIME_s*1000)/cTaskTime) //tasks
#define cSLEEP_TIME_Tasks   ((uint16_t) (cSLEEP_TIME_s*1000)/cTaskTime)  //tasks
#define cDEAD_ALIVE_Tasks   ((uint16_t) cDEAD_ALIVE_ms/cTaskTime)        //tasks

#endif