#include "../headers/translate_state.h"
#include "../dependencies/c_datastructures/headers/linked_list.h"
#include <stdlib.h>
#include <stdio.h>

struct frame {
    unsigned height;
    unsigned width;
    char **content;
};

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
            ret -> content[i][j] = '0';
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
        ret -> content[position -> y][position -> x] = '1';
    }

    return ret;
}

void print_frame(frame *frame_ptr){
    if(frame_ptr == NULL){
        return;
    }

    for(unsigned i = 0 ; i < frame_ptr -> height ; i++){
        printf("%s\n" , frame_ptr -> content[i]);
    }
}