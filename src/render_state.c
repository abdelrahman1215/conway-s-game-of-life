#include "../headers/render_state.h"
#include "../dependencies/c_datastructures/headers/linked_list.h"
#include <stdlib.h>
#include <pdcurses/curses.h>

struct frame {
    unsigned height;
    unsigned width;
    char **content;
};

#define empty_cell '.'
#define alive_cell '#'

frame *new_frame(unsigned width , unsigned height){
    //used <= 0 instead of == 0 although it is unsigned to silence a clang-tidy warning
    if(width <= 0 || height <= 0){
        return NULL;
    }

    frame *ret = calloc(1 , sizeof(frame));
    if(ret == NULL){
        return NULL;
    }

    char *tmp = calloc(height * (width + 1) , sizeof(char));
    if(tmp == NULL){
        free(ret);
        return NULL;
    }

    ret -> content = calloc(height , sizeof(char *));
    if(ret -> content == NULL){
        free(ret);
        free(tmp);
        return NULL;
    }

    for(unsigned i = 0 ; i < height ; i++){
        ret -> content[i] = tmp + (i * (width + 1));
        for(unsigned j = 0 ; j < width ; j++){
            ret -> content[i][j] = empty_cell;
        }

        ret -> content[i][width] = '\000';
    }

    ret -> width = width;
    ret -> height = height;

    return ret;
}

void destroy_frame(frame *frame_ptr){
    if(frame_ptr == NULL){
        return;
    }

    free(frame_ptr -> content[0]);
    free(frame_ptr -> content);
    free(frame_ptr);
}

frame *translate_state(board_state *state_ptr){
    if(state_ptr == NULL){
        return NULL;
    }

    linked_list *alive_cells = alive_list(state_ptr);
    if(alive_cells == NULL){
        return NULL;
    }

    unsigned frame_height = get_board_height(state_ptr);
    unsigned frame_width = get_board_width(state_ptr);

    frame *ret = new_frame(frame_width , frame_height);
    if(ret == NULL){
        return NULL;
    }


    coord *position;
    for(node *nd = linked_list_get_first_node(alive_cells) ; nd != NULL ; nd = linked_list_get_next_node(nd)){
        position = linked_list_get_obj_ptr(nd);
        ret -> content[position -> y][position -> x] = alive_cell;
    }

    return ret;
}

i128 min(i128 val_1 , i128 val_2){
    return val_1 < val_2 ? val_1 : val_2;
}

void render_state(board_state *state_ptr , WINDOW *target_win , unsigned start_x , unsigned start_y , unsigned end_x , unsigned end_y){
    if(state_ptr == NULL){
        return;
    }

    frame *translation = translate_state(state_ptr);
    if(translation == NULL) return;

    if(target_win == NULL){
        destroy_frame(translation);
        return;
    }

    if(start_x >= end_x || start_y >= end_y){
        destroy_frame(translation);
        return;
    }

    unsigned win_width = getmaxx(target_win) , win_height = getmaxy(target_win);
    if(end_x > win_width || end_y > win_height){
        destroy_frame(translation);
        return;
    }

    if(end_x - start_x > translation -> width || end_y - start_y > translation -> height){
        destroy_frame(translation);
        return;
    }


    unsigned row_width = min(win_width , end_x - start_x) + 1;
    char row[row_width];
    row[row_width - 1] = '\000';

    for(unsigned i = 0 , cur_y = start_y ; i < end_y - start_y && i < translation -> height && cur_y < end_y ; i++ , cur_y ++){
        for(unsigned j = 0 ; j < translation -> width && (j * 2) + 1 < row_width ; j++){
            row[(j * 2) + 1] = ' ';
            row[j * 2] = translation -> content[i][j];
        }

        mvwprintw(target_win , cur_y , start_x , "%s" , row);
    }
    
    refresh();
    destroy_frame(translation);
}