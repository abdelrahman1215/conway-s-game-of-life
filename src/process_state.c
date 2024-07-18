#include <stdlib.h>
#include "../headers/board_state.h"
#include "../headers/process_state.h"
#include "../c_datastructures/headers/linked_list.h"
#include "../c_datastructures/headers/dynamic_array.h"
#include <stddef.h>

i64 alive_neighbors(board_state *state_ptr , i64 x , i64 y){
    if(state_ptr == NULL)return -1;
    if(x >= get_board_width(state_ptr) || y >= get_board_height(state_ptr)) return -1;
    unsigned ret = 0;
    bool log_lookup = lookup_cell_state(state_ptr , x , y , false) == alive;
    unsigned state_width = get_board_width(state_ptr) , state_height = get_board_height(state_ptr);

    for(u128 i = x - 1 ; i <= x + 1 ; i++ ){
        if(i < 0 || i >= state_width){
            continue;
        }

        for(u128 j = y - 1 ; j <= y + 1 ; j++){
            if(j < 0 || j >= state_height ||(i == x && j == y)){
                continue;
            }

            ret += lookup_cell_state(state_ptr , i , j , log_lookup);
        }

        
    }

    return ret;
}

typedef struct set_target{
    unsigned x , y;
    cell_state new_state;
} set_target;

void update_board_state(board_state *state_ptr){
    dynamic_array *set_list = new_dynamic_array(sizeof(set_target) , NULL);
    coord *position;
    unsigned char alive_cells = 0;

    u64 i = 0;
    cell_state state;
    set_target set;

    lock_state();

    linked_list *check_list = get_check_list(state_ptr);

    for(node *nd = linked_list_get_first_node(check_list) ; nd != NULL ; nd = linked_list_get_next_node(nd)){
        position  = (coord *)linked_list_get_obj_ptr(nd);
        alive_cells = alive_neighbors(state_ptr , position -> x , position -> y);
        state = lookup_cell_state(state_ptr , position -> x , position -> y , false);

        set.x = position -> x;
        set.y = position -> y;

        if(state == alive && (alive_cells <= 1 || alive_cells > 3)){

            set.new_state = dead;
            
        }else if(state == dead && alive_cells == 3){
            
            set.new_state = alive;
            
        }else{
            
            set.new_state = state;
            
        }

        dynamic_array_add_element(set_list , &set);
    }

    reset_board(state_ptr);
    
    set_target *set_ptr = NULL;
    u64 max = dynamic_array_get_elements_no(set_list);
    for(u64 i  = 0 ; i < max  ; i++){

        set_ptr = (set_target *)dynamic_array_get_element(set_list , i);
        set_cell(state_ptr , set_ptr -> x , set_ptr -> y , set_ptr -> new_state);
    }

    unlock_state();

    destroy_dynamic_array(set_list);
}