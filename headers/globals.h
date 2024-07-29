#ifndef GLOBALS_H
#define GLOBALS_H

#include "board_state.h"
#include <pthread.h>
#include <stddef.h>

#define speed_limit 100

#define GLOBAL __attribute__((__common__))

GLOBAL unsigned Speed;
GLOBAL board_state *Board;
GLOBAL pthread_mutex_t Board_State_Mutex;
GLOBAL unsigned State_Start_X , State_Start_Y , State_End_X , State_End_Y;
GLOBAL unsigned Exit_Start_X , Exit_End_X ,  Exit_Y ;
GLOBAL unsigned Play_Start_X , Play_End_X ,  Play_Y ;
GLOBAL unsigned Reset_Start_X , Reset_End_X ,  Reset_Y ;
GLOBAL bool Pause;
GLOBAL unsigned X_Indent , Y_Indent;
GLOBAL unsigned Win_Width , Win_Height;
GLOBAL pthread_mutex_t IO_Mutex , Speed_Mutex , High_Mutex;

#endif