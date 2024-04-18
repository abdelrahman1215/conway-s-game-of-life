#include <stdlib.h>
#include <stdio.h>
#include "../headers/board_state.h"
#include "../headers/process_state.h"
#include <stddef.h>

i64 alive_neighbors(board_state *state_ptr , i64 x , i64 y){
    if(state_ptr == NULL)return -1;
    if(x >= get_board_width(state_ptr) || y >= get_board_height(state_ptr)) return -1;
    unsigned ret = 0;
    bool log_lookup = lookup_cell_state(state_ptr , x , y , false) == alive;
    unsigned state_width = get_board_width(state_ptr) , state_height = get_board_height(state_ptr);

    for(i64 i , j , iter = 0 ; iter < 8 ; iter++){
        switch(iter){
            case 0 :
                i = x;
                j = y - 1;
                break;
            case 1 :
                i = x + 1;
                j = y - 1;
                break;
            case 2 :
                i = x + 1;
                j = y;
                break;
            case 3 :
                i = x + 1;
                j = y + 1;
                break;
            case 4 :
                i = x;
                j = y + 1;
                break;
            case 5 :
                i = x - 1;
                j = y + 1;
                break;
            case 6 :
                i = x - 1;
                j = y;
                break;
            case 7 :
                i = x - 1;
                j = y - 1;
                break;
        }

        if(i < 0 || i >= state_width || j < 0 || j >= state_height){
            continue;
        }

        ret += lookup_cell_state(state_ptr , i , j , log_lookup);
        
    }

    return ret;
}

board_state *update_board_state(board_state *state_ptr){
    board_state *ret =  new_board_state(get_board_width(state_ptr) , get_board_height(state_ptr));
    coord *position;
    unsigned char alive_cells = 0;

    u64 i = 0;
    cell_state state;

    for(node *nd = linked_list_get_first_node(get_check_list(state_ptr)) ; nd != NULL ; nd = linked_list_get_next_node(nd) , i++){
        position  = (coord *)linked_list_get_obj_ptr(nd);
        alive_cells = alive_neighbors(state_ptr , position -> x , position -> y);
        state = lookup_cell_state(state_ptr , position -> x , position -> y , false);

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