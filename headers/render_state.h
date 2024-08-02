#ifndef TRANSLATE_STATE_H
#define TRANSLATE_STATE_H

#include "../headers/board_state.h"
#include <ncursesw/curses.h>

#define cell_highlight_index 4

typedef struct frame frame;

frame *new_frame(unsigned width , unsigned height);
void destroy_frame(frame *frame_ptr);

frame *translate_state(board_state *state_ptr);

void highlight_cell(unsigned short x , unsigned short y);
void unhighlight_cells();

void render_state(board_state *state_ptr , WINDOW *target_win , unsigned start_x , unsigned start_y , unsigned end_x , unsigned end_y);

#endif