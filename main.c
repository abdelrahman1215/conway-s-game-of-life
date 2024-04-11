#include "headers/translate_state.h"
#include "headers/process_state.h"
#include "headers/board_state.h"
#include <assert.h>
#include <time.h>

int main(){
    board_state *test_state = new_board_state(20 , 20);
    set_cell(test_state , 1 , 0 , alive);
    set_cell(test_state , 2 , 1 , alive);
    set_cell(test_state , 0 , 2 , alive);
    set_cell(test_state , 1 , 2 , alive);
    set_cell(test_state , 2 , 2 , alive);

    lookup_cell_state(test_state , 0 , 1);
    lookup_cell_state(test_state , 0 , 1);
    lookup_cell_state(test_state , 0 , 1);


    frame *test_frame;

    struct timespec spec = {.tv_nsec = 0 , .tv_sec = 1};

    board_state *old_state;
    for(unsigned i = 0 ; i < 10 ; i++){
        test_frame = translate_state(test_state);

        system("cls");
        print_frame(test_frame);

        old_state = test_state;
        test_state = update_board_state(test_state);
        destroy_board_state(old_state);

        nanosleep(&spec , NULL);
    }

    destroy_frame(test_frame);
    destroy_board_state(test_state);
}