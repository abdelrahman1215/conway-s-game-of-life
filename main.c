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

    pthread_mutex_init(&Print_Mutex , NULL);

    const unsigned nano_per_sec = 1000000000;
    Speed = 2;
    struct timespec spec = {.tv_nsec =  nano_per_sec / Speed, .tv_sec = 0};

    Pause = true;

    initscr();
    refresh();
    curs_set(0);
    nodelay(stdscr , true);
    noecho();
    box(stdscr , 0 , 0);

    Win_Width = getmaxx(stdscr) ;
    Win_Height = getmaxy(stdscr);

    Board = new_board_state(Win_Height * 3 , Win_Width * 3);

    X_Indent = Win_Width;
    Y_Indent = Win_Height;

    State_Start_X = 2;
    State_Start_Y = 1;

    State_End_X = Win_Width - 1;
    State_End_Y = Win_Height - 2;

    pthread_t input_thread , play_thread , speed_thread , coord_thread;
    pthread_create(&input_thread , NULL , handle_input , NULL );
    pthread_create(&play_thread , NULL , print_pause_play_state , NULL );
    pthread_create(&speed_thread , NULL , print_speed , NULL );
    pthread_create(&coord_thread , NULL , display_coord , NULL );
    render_exit_button();
    render_play_pause_button();
    render_reset_button();

    while(1){
        
        render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);

        if(Pause == false){
            pthread_mutex_unlock(&Speed_Mutex);
            if(Speed == 1){
                spec.tv_sec = 1;
                spec.tv_nsec = 0;
            }else{
                spec.tv_sec = 0;
                spec.tv_nsec = nano_per_sec / Speed;
            }
            pthread_mutex_unlock(&Speed_Mutex);

            update_board_state(Board);
            nanosleep(&spec , NULL);
        }
    }

    endwin();


    destroy_board_state(Board);
}
