#include "../headers/globals.h"
#include "../headers/interface.h"
#include "../headers/board_state.h"
#include <pdcurses.h>
#include <pthread.h>
#include <stddef.h>

void print_pause_play_state(){
    if(stdscr == NULL) pthread_exit(NULL);

    pthread_mutex_lock(&IO_Mutex);

    move( 0 , (Win_Width - 8) / 2 - 1 );
    if(Pause == true){
        attron(COLOR_PAIR(button_index));
        printw(" paused ");
        attroff(COLOR_PAIR(button_index));
        
        attron(COLOR_PAIR(2));
        printw("%c" , 196 );
        attroff(COLOR_PAIR(2));
    }else{
        attron(COLOR_PAIR(button_index));
        printw(" playing ");
        attroff(COLOR_PAIR(button_index));
    }
    
    pthread_mutex_unlock(&IO_Mutex);
}

void display_coord(void ){
    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_index));
    mvprintw( 0 , 2 , " %i , %i " , X_Indent , Y_Indent );
    attroff(COLOR_PAIR(button_index));

    attron(COLOR_PAIR(2));
    printw("%c%c%c%c" , 196 , 196 , 196 , 196 );
    attroff(COLOR_PAIR(2));

    pthread_mutex_unlock(&IO_Mutex);

}

void print_speed(){
    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_index));
    mvprintw( Play_Y , Play_End_X + 4 , " %ix " , Speed);
    attroff(COLOR_PAIR(button_index));

    attron(COLOR_PAIR(2));
    printw("%c%c" , 196 , 196 );
    attroff(COLOR_PAIR(2));

    pthread_mutex_unlock(&IO_Mutex);   
}

void render_exit_button(){
    if(stdscr == NULL) return;

    Exit_Start_X = 2;
    Exit_End_X = Exit_Start_X + 4;
    Exit_Y = Win_Height - 1;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_index));
    mvprintw(Exit_Y , Exit_Start_X , " exit ");
    attroff(COLOR_PAIR(button_index));

    pthread_mutex_unlock(&IO_Mutex);
}

void highlight_exit_button(){
    if(stdscr == NULL) return;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_highlight_index));
    mvprintw(Exit_Y , Exit_Start_X , " exit ");
    attroff(COLOR_PAIR(button_highlight_index));

    pthread_mutex_unlock(&IO_Mutex);
}

void render_play_pause_button(){
    if(stdscr == NULL) return;

    Play_Start_X = (Win_Width - 14) / 2;
    Play_End_X = Play_Start_X + 14;
    Play_Y = Win_Height - 1;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_index));
    mvprintw( Play_Y , Play_Start_X , " play / pause ");
    attroff(COLOR_PAIR(button_index));

    pthread_mutex_unlock(&IO_Mutex);

}

void highlight_play_pause_button(){
    if(stdscr == NULL) return;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_highlight_index));
    mvprintw( Play_Y , Play_Start_X , " play / pause ");
    attroff(COLOR_PAIR(button_highlight_index));

    pthread_mutex_unlock(&IO_Mutex);

}

void render_reset_button(){
    if(stdscr == NULL) return;
    
    Reset_Y = Play_Y;
    Reset_End_X = Play_Start_X - 4;
    Reset_Start_X = Reset_End_X - 7;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_index));
    mvprintw( Reset_Y , Reset_Start_X , " reset ");
    attroff(COLOR_PAIR(button_index));

    pthread_mutex_unlock(&IO_Mutex);
}

void highlight_reset_button(){
    if(stdscr == NULL) return;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_highlight_index));
    mvprintw( Reset_Y , Reset_Start_X , " reset ");
    attroff(COLOR_PAIR(button_highlight_index));

    pthread_mutex_unlock(&IO_Mutex);
}

void *render_interface(void *){
    if(stdscr == NULL){
        pthread_exit(0);
    }

    static unsigned int last_diplayed_speed = 0;
    static coord last_diplayed_coord = {.x = -1 , .y = -1};
    
    render_exit_button();
    render_play_pause_button();
    render_reset_button();

    print_speed();
    display_coord();   
    print_pause_play_state();

    last_diplayed_speed = Speed;
    last_diplayed_coord.x = X_Indent;
    last_diplayed_coord.y = Y_Indent;

    return NULL;
}