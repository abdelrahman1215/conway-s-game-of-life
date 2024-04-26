#include "../headers/globals.h"
#include "../headers/interface.h"
#include "../headers/board_state.h"
#include <pdcurses.h>
#include <pthread.h>
#include <stddef.h>

void *print_pause_play_state(void *){
    if(stdscr == NULL) pthread_exit(NULL);

    bool last_pause_state = !Pause;

    while(1){
        if(Pause == last_pause_state){
            continue;
        }

        pthread_mutex_lock(&Print_Mutex);

        move( 0 , (Win_Width - 8) / 2 - 1 );

        if(Pause == true){
            printw("%c paused %c" , 196 , 196 );
        }else{
            printw(" playing ");
        }

        refresh();

        pthread_mutex_unlock(&Print_Mutex);

        last_pause_state = Pause;
    }

    return NULL;
}

void render_exit_button(){
    if(stdscr == NULL) return;

    pthread_mutex_lock(&Print_Mutex);

    Exit_Start_X = 2;
    Exit_End_X = Exit_Start_X + 4;
    Exit_Y = Win_Height - 1;

    mvprintw(Exit_Y , Exit_Start_X , " exit ");

    pthread_mutex_unlock(&Print_Mutex);
}

void render_play_pause_button(){
    if(stdscr == NULL) return;

    pthread_mutex_lock(&Print_Mutex);

    Play_Start_X = (Win_Width - 14) / 2;
    Play_End_X = Play_Start_X + 14;
    Play_Y = Win_Height - 1;

    mvprintw( Play_Y , Play_Start_X , " play / pause ");

    pthread_mutex_unlock(&Print_Mutex);

}

void *print_speed(void *){
    if(stdscr == NULL) pthread_exit(NULL);

    while (1){
        pthread_mutex_lock(&Print_Mutex);

        mvprintw( Play_Y , Play_End_X + 4 , " %ix %c%c" , Speed , 196 , 196 );

        pthread_mutex_unlock(&Print_Mutex);
    }
    
    return NULL;
}

void render_reset_button(){
    if(stdscr == NULL) return;

    Reset_Y = Play_Y;
    Reset_End_X = Play_Start_X - 4;
    Reset_Start_X = Reset_End_X - 7;

    pthread_mutex_lock(&Print_Mutex);

    mvprintw( Reset_Y , Reset_Start_X , " reset ");

    pthread_mutex_unlock(&Print_Mutex);
}

void *display_coord(void *){
    if(stdscr == NULL) pthread_exit(NULL);

    while(1){
        pthread_mutex_lock(&Print_Mutex);

        mvprintw( 0 , 2 , " %i , %i %c%c%c%c" , X_Indent , Y_Indent , 196 , 196 , 196 , 196  );

        pthread_mutex_unlock(&Print_Mutex);
    }

    return NULL;
}