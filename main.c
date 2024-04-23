#include "headers/render_state.h"
#include "headers/process_state.h"
#include "headers/board_state.h"
#include "headers/globals.h"
#include "headers/input.h"
#include <assert.h>
#include <pdcurses/curses.h>
#include <time.h>

int main(){
    board = new_board_state(1000 , 1000);

    const unsigned nano_per_sec = 1000000000;
    speed = 4;
    struct timespec spec = {.tv_nsec =  nano_per_sec / speed, .tv_sec = 0};

    pause = true;

    initscr();
    refresh();
    curs_set(0);
    nodelay(stdscr , true);
    noecho();

    unsigned win_width = getmaxx(stdscr) , win_height = getmaxy(stdscr);

    state_start_x = 2;
    state_start_y = 1;

    state_end_x = win_width - 1;
    state_end_y = win_height - 2;

    pthread_t thread_id;
    pthread_create(&thread_id , NULL , handle_input , NULL );

    box(stdscr , 0 , 0);

    while(1){
        render_state(board , stdscr , state_start_x , state_start_y , state_end_x , state_end_y);

        if(pause == false){
            update_board_state(board);
            nanosleep(&spec , NULL);
        }

        //int input = getch();
        /*switch(input){
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
        }*/
    }

    pthread_join(thread_id , NULL);
    endwin();


    destroy_board_state(board);
}
