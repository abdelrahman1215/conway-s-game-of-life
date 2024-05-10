#include "../headers/globals.h"
#include "../headers/interface.h"
#include "../headers/board_state.h"
#include <ncursesw/curses.h>
#include <pthread.h>
#include <stddef.h>

void print_pause_play_state(){
    if(stdscr == NULL) pthread_exit(NULL);

    pthread_mutex_lock(&IO_Mutex);

    move( 0 , (Win_Width - 8) / 2 );
    if(Pause == true){
        printw("paused ");
    }else{
        printw("playing");
    }
    refresh();

    pthread_mutex_unlock(&IO_Mutex);
}

void display_coord(void ){
    pthread_mutex_lock(&IO_Mutex);

    mvprintw( 0 , 3 , "%i , %i     " , X_Indent , Y_Indent);


    pthread_mutex_unlock(&IO_Mutex);

}

void print_speed(){
    pthread_mutex_lock(&IO_Mutex);

    mvprintw( Play_Y , Play_End_X + 5 , "%ix  " , Speed);

    pthread_mutex_unlock(&IO_Mutex);   
}

void render_exit_button(){
    if(stdscr == NULL) return;

    Exit_Start_X = 3;
    Exit_End_X = Exit_Start_X + 5;
    Exit_Y = Win_Height - 1;

    pthread_mutex_lock(&IO_Mutex);

    mvprintw(Exit_Y , Exit_Start_X , "exit");

    pthread_mutex_unlock(&IO_Mutex);
}

void render_play_pause_button(){
    if(stdscr == NULL) return;

    Play_Start_X = (Win_Width - 14) / 2;
    Play_End_X = Play_Start_X + 14;
    Play_Y = Win_Height - 1;

    pthread_mutex_lock(&IO_Mutex);

    mvprintw( Play_Y , Play_Start_X , "play / pause");

    pthread_mutex_unlock(&IO_Mutex);

}

void render_reset_button(){
    Reset_Y = Play_Y;
    Reset_End_X = Play_Start_X - 3;
    Reset_Start_X = Reset_End_X - 7;

    pthread_mutex_lock(&IO_Mutex);

    mvprintw( Reset_Y , Reset_Start_X , "reset");

    pthread_mutex_unlock(&IO_Mutex);
}

void *render_interface(void *){
    if(stdscr == NULL){
        pthread_exit(0);
    }

    render_exit_button();
    render_play_pause_button();
    render_reset_button();

    while(1){
        display_coord();
        print_speed();
        print_pause_play_state();
    }
}