#include <stdlib.h>
#include "../headers/board_state.h"
#include "../headers/proccess.h"

#define state_width 17

typedef struct board_state{
    char state[state_width][state_width];
}board_state;

board_state empty_state(){
    board_state ret;
    for(unsigned i = 0 ; i < state_width ; i++){
        for(unsigned j = 0 ; j < state_width ; j++){
            ret.state[i][j] = 0;
        }
    }

    return ret;
}

unsigned alive_neighbors(board_state state , unsigned x , unsigned y){
    unsigned ret = 0;

    if(x < state_width){
        ret += state.state[y][x + 1];
        if(y < state_width){
            ret += state.state[y + 1][x + 1];
            ret += state.state[y + 1][x];
        }
        
        if(y > 0){
            ret += state.state[y - 1][x + 1];
            ret += state.state[y - 1][x];
        }
    }

    if(x > 0){
        ret += state.state[y][x - 1];
        if(y < state_width){
            ret += state.state[y + 1][x - 1];
            if(x == state_width){
                ret += state.state[y + 1][x];
            }
        }

        if(y > 0){
            ret += state.state[y - 1][x - 1];
            if(x == state_width){
                ret += state.state[y - 1][x];
            }
        }
    }

    return ret;
}

board_state new_state(board_state old_state){
    board_state ret = empty_state();

    char current;
    for(unsigned y = 0 ; y < state_width ; y++){
        for(unsigned x = 0 ; x < state_width ; x++){
            current = old_state.state[y][x];
            unsigned alive = alive_neighbors(old_state , x , y);
            if(current == 1 && (alive > 3 || alive <= 1)){
                ret.state[y][x] = 0;
                continue;
            }

            if(current == 0 && alive == 3){
                ret.state[y][x] = 1;
                continue;
            }

            ret.state[y][x] = old_state.state[y][x];
        }
    }

    return ret;
}