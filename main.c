#include "src/render_state.c"
#include "headers/process_state.h"
#include "headers/board_state.h"
#include <assert.h>
#include <pdcurses/curses.h>
#include <time.h>

int main(){
    board_state *test_state = new_board_state(105 , 105);
    set_cell(test_state , 1 , 0 , alive);
    set_cell(test_state , 2 , 1 , alive);
    set_cell(test_state , 0 , 2 , alive);
    set_cell(test_state , 1 , 2 , alive);
    set_cell(test_state , 2 , 2 , alive);

    frame *test_frame;

    struct timespec spec = {.tv_nsec = 0 , .tv_sec = 1};

    board_state *old_state;

    initscr();
    refresh();
    curs_set(0);
    nodelay(stdscr , true);

    unsigned win_width = getmaxx(stdscr) , win_height = getmaxy(stdscr);

    while(1){
        test_frame = translate_state(test_state);

        render_state(test_state , stdscr , 0 , 0 , win_width , win_height);

        old_state = test_state;
        test_state = update_board_state(test_state);
        destroy_board_state(old_state);

        nanosleep(&spec , NULL);
        if(getch() != ERR){
            exit(0);
        }

        destroy_frame(test_frame);
    }

    endwin();

    destroy_board_state(test_state);
}