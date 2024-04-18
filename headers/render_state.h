#ifndef TRANSLATE_STATE_H
#define TRANSLATE_STATE_H

#include "../headers/board_state.h"
#include <pdcurses/curses.h>

typedef struct frame frame;

frame *new_frame(unsigned width , unsigned height);
void destroy_frame(frame *frame_ptr);

frame *translate_state(board_state *state_ptr);

void render_state(board_state *state_ptr , WINDOW *target_win , unsigned start_x , unsigned start_y , unsigned end_x , unsigned end_y);

#endif