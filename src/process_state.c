#include <stdlib.h>
#include "../headers/board_state.h"
#include "../headers/process_state.h"

i64 alive_neighbors(board_state *state_ptr , unsigned x , unsigned y){
    if(state_ptr == NULL)return -1;
    if(x >= get_board_width(state_ptr) || y >= get_board_height(state_ptr)) return -1;
    unsigned ret = 0;

    if(x < get_board_width(state_ptr)){
        ret += lookup_cell_state(state_ptr , x + 1 , y);
        if(y < get_board_height(state_ptr)){
            ret += lookup_cell_state(state_ptr , x + 1 , y + 1);
            ret += lookup_cell_state(state_ptr , x , y + 1);
        }
        
        if(y > 0){
            ret += lookup_cell_state(state_ptr , x + 1 , y - 1);
            ret += lookup_cell_state(state_ptr , x , y - 1);
        }
    }

    if(x > 0){
        ret += lookup_cell_state(state_ptr , x - 1 , y);
        if(y < get_board_height(state_ptr)){
            ret += lookup_cell_state(state_ptr , x - 1 , y + 1);
            if(x == get_board_width(state_ptr)){
                ret += lookup_cell_state(state_ptr , x , y + 1);
            }
        }

        if(y > 0){
            ret += lookup_cell_state(state_ptr , x - 1 , y - 1);
            if(x == get_board_width(state_ptr)){
                ret += lookup_cell_state(state_ptr , x , y - 1);
            }
        }
    }

    return ret;
}

/*unsigned alive_neighbors(board_state *state , unsigned x , unsigned y){
    unsigned ret = 0;

    if(x < state_width){
        ret += state -> cells[y][x + 1].state;
        if(y < state_width){
            ret += state-> cells[y + 1][x + 1].state;
            ret += state-> cells[y + 1][x].state;
        }
        
        if(y > 0){
            ret += state -> cells[y - 1][x + 1].state;
            ret += state-> cells[y - 1][x].state;
        }
    }

    if(x > 0){
        ret += state -> cells[y][x - 1].state;
        if(y < state_width){
            ret += state -> cells[y + 1][x - 1].state;
            if(x == state_width){
                ret += state -> cells[y + 1][x].state;
            }
        }

        if(y > 0){
            ret += state -> cells[y - 1][x - 1].state;
            if(x == state_width){
                ret += state -> cells[y - 1][x].state;
            }
        }
    }

    return ret;
}*/

board_state *update_board_state(board_state *state_ptr){
    board_state *ret =  new_board_state(get_board_width(state_ptr) , get_board_height(state_ptr));
    coord *position;
    unsigned char alive_cells = 0;

    u64 i = 0;
    cell_state state;

    for(node *nd = linked_list_get_first_node(get_check_list(state_ptr)) ; nd != NULL ; nd = linked_list_get_next_node(nd) , i++){
        position  = (coord *)linked_list_get_obj_ptr(nd);
        alive_cells = alive_neighbors(state_ptr , position -> x , position -> y);
        state = lookup_cell_state(state_ptr , position -> x , position -> y);
        if(state == alive && (alive_cells <= 1 || alive_cells > 3)){

            set_cell(ret , position -> x , position -> y , dead);
            
        }else if(state == dead && alive_cells == 3){
            
            set_cell(ret , position -> x , position -> y , alive);
            
        }else{
            
            set_cell(ret , position -> x , position -> y , state);
            
        }
    }

    return ret;
}