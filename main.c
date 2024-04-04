#include "src/board_state.c"
#include <assert.h>

int main(){
    board_state *test = new_board_state(10 , 10);

    set_cell(test , 0 , 1 , alive);
    set_cell(test , 0 , 1 , dead);

    destroy_board_state(test);
}