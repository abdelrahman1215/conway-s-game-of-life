#include <stdlib.h>
#include "../src/board_state.c"
#include "../headers/proccess.h"

#define state_width 17

cell_state check(board_state *state_ptr , unsigned x , unsigned y){
    coord position = {.x = x , .y = y};

    if(state_ptr -> cells[y][x].state == 0 && state_ptr -> cells[y][x].lookups == 3){
        position.x = x;
        position.y = y;
        linked_list_add_node(&position , sizeof(coord) , NULL , state_ptr -> check_list);
    }

    return state_ptr -> cells[y][x].state;
}

unsigned char alive_neighbors(board_state *state , unsigned x , unsigned y){
    unsigned ret = 0;

    if(x < state_width){
        ret += check(state , x + 1 , y);
        if(y < state_width){
            ret += check(state , x + 1 , y + 1);
            ret += check(state , x , y + 1);
        }
        
        if(y > 0){
            ret += check(state , x + 1 , y - 1);
            ret += check(state , x , y - 1);
        }
    }

    if(x > 0){
        ret += check(state , x - 1 , y);
        if(y < state_width){
            ret += check(state , x - 1 , y + 1);
            if(x == state_width){
                ret += check(state , x , y + 1);
            }
        }

        if(y > 0){
            ret += check(state , x - 1 , y - 1);
            if(x == state_width){
                ret += check(state , x , y - 1);
            }
        }
    }

    return ret;
}

board_state *update_board_state(board_state *state_ptr){
    board_state *ret =  new_board_state(state_ptr -> height , state_ptr -> height);
    coord *position;
    unsigned char alive_cells = 0;

    u64 i = 0;
    for(node *nd = linked_list_get_first_node(state_ptr -> check_list) ; nd != NULL ; nd = linked_list_get_next_node(nd) , i++){
        position  = (coord *)linked_list_get_obj_ptr(nd);
        alive_cells = alive_neighbors(state_ptr , position -> x , position -> y);
        if(state_ptr -> cells[position -> y][position -> x].state == alive && (alive_cells <= 1 || alive_cells > 3)){
            set_cell(ret , position -> x , position -> y , dead);
        }else if(state_ptr -> cells[position -> y][position -> x].state == alive && alive_cells == 3){
            set_cell(ret , position -> x , position -> y , alive);
        }else{
            set_cell(ret , position -> x , position -> y , state_ptr -> cells[position -> y][position -> x].state);
        }

        if(state_ptr -> cells[position -> y][position -> x].state == dead){
            linked_list_delete_node(i , state_ptr -> check_list);
            i--;
        }
    }

    return ret;
}