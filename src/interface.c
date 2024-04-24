#include "../headers/globals.h"
#include <pdcurses.h>
#include <pthread.h>
#include <stddef.h>

void *print_pause_play_state(void *){
    if(stdscr == NULL){
        return NULL;
    }

    bool last_pause_state = !pause;

    while(1){
        if(pause == last_pause_state){
            continue;
        }

        pthread_mutex_lock(&print_mutex);

        move( 0 , (win_width - 8) / 2 - 1 );

        if(pause == true){
            printw("%c paused %c" , 196 , 196 );
        }else{
            printw(" playing ");
        }

        refresh();

        pthread_mutex_unlock(&print_mutex);

        last_pause_state = pause;
    }

    return NULL;
}

void render_exit_button(){
    pthread_mutex_lock(&print_mutex);

    exit_start_x = 2;
    exit_end_x = exit_start_x + 4;
    exit_y = win_height - 1;

    mvprintw(exit_y , exit_start_x , " exit ");

    pthread_mutex_unlock(&print_mutex);
}

void render_play_pause_button(){
    pthread_mutex_lock(&print_mutex);

    play_start_x = (win_width - 14) / 2;
    play_end_x = play_start_x + 14;
    play_y = win_height - 1;

    mvprintw( play_y , play_start_x , " play / pause ");

    pthread_mutex_unlock(&print_mutex);
}