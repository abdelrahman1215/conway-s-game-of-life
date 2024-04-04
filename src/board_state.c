#ifndef BOARD_STATE_C
#define BOARD_STATE_C

#include <stdlib.h>
#include "../dependencies/c_datastructures/headers/linked_list.h"

typedef enum cell_state{dead = 0 , alive = 1} cell_state;

#define state_err -1

typedef struct cell{
    cell_state state;
    unsigned lookups;
}cell;

typedef struct board_state{
    unsigned width , height;
    cell **cells;
    linked_list *check_list;
}board_state;

typedef struct coord{
    unsigned x , y;
}coord;



board_state *new_board_state(unsigned height , unsigned width){
    if(height == 0 || width == 0){
        return NULL;
    }

    board_state *ret = (board_state *)calloc(1 , sizeof(board_state));
    if(ret == NULL) return NULL;

    ret -> height = height;
    ret -> width = width;

    cell *cells = (cell *)calloc(height * width , sizeof(cell));
    if(cells == NULL){
        free(ret);
        return NULL;
    }

    ret -> cells = (cell **)calloc(height , sizeof(cell*));
    if(ret -> cells == NULL){
        free(ret);
        free(cells);
        return NULL;
    }

    for(unsigned i = 0 ; i < height ; i++){
        ret -> cells[i] = cells + (i * width);
    }

    ret -> check_list = new_linked_list();
    if(ret -> check_list == NULL){
        free(ret -> cells);
        free(ret);
        free(cells);
        return NULL;
    }

    return ret;
}

void destroy_board_state(board_state *state_ptr){
    if(state_ptr == NULL) return;

    destroy_linked_list(state_ptr -> check_list);
    free(state_ptr -> cells[0]);
    free(state_ptr -> cells);
    free(state_ptr);
}

void set_cell(board_state *state_ptr , unsigned x , unsigned y , cell_state new_state){
    if(state_ptr == NULL) return;
    if(x >= state_ptr -> width || y >= state_ptr -> height) return;
    if(new_state > 1 || new_state < 0) return;

    cell *target = state_ptr -> cells[y] + x;
    coord position = {.x = x , .y = y};
    if(new_state == alive && target -> state == dead){
        linked_list_add_node(&position , sizeof(coord) , NULL , state_ptr -> check_list);
    }else if(new_state == dead && target -> state == alive){
        node *nd = linked_list_get_first_node(state_ptr -> check_list);
        coord *cd;

        for(u64 i = 0 ; nd != NULL ; nd = linked_list_get_next_node(nd) , i++){
            cd = linked_list_get_obj_ptr(nd);
            if(*(u64 *)cd== *(u64 *)&position){
                linked_list_delete_node(i , state_ptr -> check_list);
                break;
            }
        }
    }

    target -> state = new_state;
}

cell_state lookup_cell_state(board_state *state_ptr , unsigned x , unsigned y){
    if(state_ptr == NULL) return state_err;
    if(x >= state_ptr -> width || y >= state_ptr -> height) return state_err;

    cell target = state_ptr -> cells[y][x];
    target.lookups++;
    
    return target.state;
}

#endif