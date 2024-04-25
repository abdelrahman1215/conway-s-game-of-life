#ifndef BOARD_STATE_H
#define BOARD_STATE_H
#include "../c_datastructures/headers/linked_list.h"
#include <stddef.h>

typedef struct board_state board_state;

typedef struct coord{
    unsigned x , y;
}coord;

typedef enum cell_state{dead = 0 , alive = 1} cell_state;
#define state_err -1

board_state *new_board_state(unsigned height , unsigned width);
void destroy_board_state(board_state *state_ptr);

void set_cell(board_state *state_ptr , unsigned x , unsigned y , cell_state new_state);

cell_state lookup_cell_state(board_state *state_ptr , unsigned x , unsigned y , bool log_lookup);

linked_list *alive_list(board_state *state_ptr);

i64 get_board_width(board_state *state_ptr);
i64 get_board_height(board_state *state_ptr);
linked_list *get_check_list(board_state *state_ptr);

void reset_board(board_state *state_ptr);

void lock_state();
void unlock_state();
#endif