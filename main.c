#include "headers/render_state.h"
#include "headers/process_state.h"
#include "headers/board_state.h"
#include <assert.h>
#include <pdcurses/curses.h>
#include <time.h>

int main(){
    board_state *test_state = new_board_state(1000 , 1000);
    set_cell(test_state , 2 , 1 , alive);
    set_cell(test_state , 3 , 2 , alive);
    set_cell(test_state , 1 , 3 , alive);
    set_cell(test_state , 2 , 3 , alive);
    set_cell(test_state , 3 , 3 , alive);

    const unsigned nano_per_sec = 1000000000;
    struct timespec spec = {.tv_nsec =  nano_per_sec / 2, .tv_sec = 0};

    board_state *old_state;

    FILE *debug = fopen("debug.txt" , "w");

    fprintf(debug , "test");

    fclose(debug);

    initscr();
    refresh();
    curs_set(0);
    nodelay(stdscr , true);
    noecho();

    unsigned win_width = getmaxx(stdscr) , win_height = getmaxy(stdscr);

    while(1){
        flushinp();
        render_state(test_state , stdscr , 0 , 0 , win_width , win_height - 1);

        old_state = test_state;
        test_state = update_board_state(test_state);
        destroy_board_state(old_state);

        nanosleep(&spec , NULL);
        int input = getch();
        switch(input){
            case 'q':
            case 'Q':
                exit(0);
                break;

            case ' ':
            case 'p':
            case 'P':
                input = '\000';

                while(input != 'r' && input != 'R' && input != 'q' && input != 'Q' && input != ' '){
                    input = getch();
                }

		        if(input == 'q' || input == 'Q'){
		            exit(0);		
		        }

                break;
        }
    }

    endwin();

    destroy_board_state(test_state);
}
