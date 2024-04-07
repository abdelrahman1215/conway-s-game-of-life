#ifndef BOARD_STATE_H
#define BOARD_STATE_H
#include "../dependencies/c_datastructures/headers/linked_list.h"

typedef struct board_state board_state;
typedef enum cell_state{dead = 0 , alive = 1} cell_state;
#define state_err -1

board_state *new_board_state(unsigned height , unsigned width);
void destroy_board_state(board_state *state_ptr);

void set_cell(board_state *state_ptr , unsigned x , unsigned y , cell_state new_state);

linked_list *alive_list(board_state *state_ptr);

#endif