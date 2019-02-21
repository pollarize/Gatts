/*
 * System_Types.hpp
 *
 *  Created on: Sep 17, 2017
 *      Author: Mihail Maldzhanski
 */

#ifndef MAIN_CONFIG_SYSTEM_TYPES_HPP_
#define MAIN_CONFIG_SYSTEM_TYPES_HPP_

//Define specific types for the system
#ifndef SYSTEM_TYPES

typedef enum E_Sys_ReturnType
{
    SYS_OK,      /*0*/
    SYS_NOT_OK,  /*1*/
    SYS_PENDING, /*2*/
    SYS_Count
}Sys_ReturnType;

typedef unsigned char boolean;

#ifndef TRUE
    #define FALSE 0
    #define TRUE (0!=1)
#endif

#endif

#ifndef NULL
    #ifdef __cplusplus
        #define NULL 0
    #else
        #define NULL ((void *)0)
    #endif
#endif

#endif /* MAIN_CONFIG_SYSTEM_TYPES_HPP_ */
