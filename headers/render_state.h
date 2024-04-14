#ifndef TRANSLATE_STATE_H
#define TRANSLATE_STATE_H

#include "../headers/board_state.h"

typedef struct frame frame;

frame *new_frame(unsigned width , unsigned height);
void destroy_frame(frame *frame_ptr);

frame *translate_state(board_state *state_ptr);

void print_frame(frame *frame_ptr);

#endif