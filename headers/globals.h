#ifndef GLOBALS_H
#define GLOBALS_H

#include "board_state.h"
#include <pthread.h>
#include <stddef.h>

#define global __attribute__((__common__))

global unsigned speed;
global board_state *board;
global pthread_mutex_t board_state_mutex;
global unsigned state_start_x , state_start_y , state_end_x , state_end_y;
global bool pause;

#endif