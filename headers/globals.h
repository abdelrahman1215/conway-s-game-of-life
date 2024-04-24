#ifndef GLOBALS_H
#define GLOBALS_H

#include "board_state.h"
#include <pthread.h>
#include <stddef.h>

#define speed_limit 100

#define global __attribute__((__common__))

global unsigned speed;
global board_state *board;
global pthread_mutex_t board_state_mutex;
global unsigned state_start_x , state_start_y , state_end_x , state_end_y;
global unsigned exit_start_x , exit_end_x ,  exit_y ;
global unsigned play_start_x , play_end_x ,  play_y ;
global unsigned reset_start_x , reset_end_x ,  reset_y ;
global bool pause;
global unsigned x_indent , y_indent;
global unsigned win_width , win_height;
global pthread_mutex_t print_mutex;
global pthread_mutex_t speed_mutex;

#endif