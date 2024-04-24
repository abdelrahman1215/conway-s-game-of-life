#include "headers/process_state.h"
#include "headers/render_state.h"
#include "headers/board_state.h"
#include "headers/interface.h"
#include "headers/globals.h"
#include "headers/input.h"

#include <pdcurses/curses.h>
#include <assert.h>
#include <time.h>

int main(){

    pthread_mutex_init(&print_mutex , NULL);

    const unsigned nano_per_sec = 1000000000;
    speed = 3;
    struct timespec spec = {.tv_nsec =  nano_per_sec / speed, .tv_sec = 0};

    pause = true;

    initscr();
    refresh();
    curs_set(0);
    nodelay(stdscr , true);
    noecho();
    box(stdscr , 0 , 0);

    win_width = getmaxx(stdscr) ;
    win_height = getmaxy(stdscr);

    board = new_board_state(win_height * 3 , win_width * 3);

    x_indent = win_width;
    y_indent = win_height;

    state_start_x = 2;
    state_start_y = 1;

    state_end_x = win_width - 1;
    state_end_y = win_height - 2;

    pthread_t input_thread , interface_thread;
    pthread_create(&input_thread , NULL , handle_input , NULL );
    pthread_create(&interface_thread , NULL , print_pause_play_state , NULL );
    render_exit_button();
    render_play_pause_button();

    while(1){

        /*(move( 0 , (win_width - 8) / 2 - 1 );
        if(pause == true){
            printw("%c puased %c" , 196 , 196 );
        }else{
            printw(" playing ");
        }*/

        render_state(board , stdscr , state_start_x , state_start_y , state_end_x , state_end_y);

        if(pause == false){
            update_board_state(board);
            nanosleep(&spec , NULL);
        }
    }

    endwin();


    destroy_board_state(board);
}
