#include "../headers/globals.h"
#include "../headers/interface.h"
#include "../headers/board_state.h"
#include <pdcurses.h>
#include <pthread.h>
#include <stddef.h>
#include <math.h>

bool play_button_high = false , exit_button_high = false , reset_button_high = false;

void print_pause_play_state(){
    if(stdscr == NULL) pthread_exit(NULL);

    pthread_mutex_lock(&IO_Mutex);

    move( 0 , (Win_Width - 8) / 2 - 1 );
    if(Pause == true){
        attron(COLOR_PAIR(button_index));
        printw(" paused ");
        attroff(COLOR_PAIR(button_index));
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

    pthread_mutex_unlock(&IO_Mutex);

}

void print_speed(){
    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_index));
    mvprintw( Play_Y , Play_End_X + 4 , " %ix " , Speed);
    attroff(COLOR_PAIR(button_index));

    pthread_mutex_unlock(&IO_Mutex);   
}

void render_exit_button(){
    if(stdscr == NULL) return;

    Exit_Start_X = 2;
    Exit_End_X = Exit_Start_X + 4;
    Exit_Y = Win_Height - 1;

    int button_pair = button_index;
    if(exit_button_high) button_pair = button_highlight_index;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_pair));
    mvprintw(Exit_Y , Exit_Start_X , " exit ");
    attroff(COLOR_PAIR(button_pair));

    pthread_mutex_unlock(&IO_Mutex);
}

void highlight_exit_button(){
    exit_button_high = true;
}

void unhighlight_exit_button(){
    exit_button_high = false;
}

void render_play_pause_button(){
    if(stdscr == NULL) return;

    Play_Start_X = (Win_Width - 14) / 2;
    Play_End_X = Play_Start_X + 14;
    Play_Y = Win_Height - 1;

    int button_pair = button_index;
    if(play_button_high) button_pair = button_highlight_index;
    
    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_pair));
    mvprintw( Play_Y , Play_Start_X , " play / pause ");
    attroff(COLOR_PAIR(button_pair));

    pthread_mutex_unlock(&IO_Mutex);

}

void highlight_play_pause_button(){
   play_button_high = true;
}

void unhighlight_play_pause_button(){
   play_button_high = false;
}

void render_reset_button(){
    if(stdscr == NULL) return;
    
    Reset_Y = Play_Y;
    Reset_End_X = Play_Start_X - 4;
    Reset_Start_X = Reset_End_X - 7;

    int button_pair = button_index;
    if(reset_button_high) button_pair = button_highlight_index;

    pthread_mutex_lock(&IO_Mutex);

    attron(COLOR_PAIR(button_pair));
    mvprintw( Reset_Y , Reset_Start_X , " reset ");
    attroff(COLOR_PAIR(button_pair));

    pthread_mutex_unlock(&IO_Mutex);
}

void highlight_reset_button(){
    reset_button_high = true;
}

void unhighlight_reset_button(){
    reset_button_high = false;
}

void *render_interface(void *){
    if(stdscr == NULL){
        pthread_exit(0);
    }

    static int called = false;
    static unsigned int last_diplayed_speed = 0;
    static coord last_diplayed_coord = {.x = -1 , .y = -1};
    static bool last_diplayed_play_pause_state = true;

    if(log10(last_diplayed_coord.x) != log10(X_Indent) || log10(last_diplayed_coord.y) != log10(Y_Indent) || last_diplayed_play_pause_state != Pause || last_diplayed_speed != Speed){
        pthread_mutex_lock(&IO_Mutex);

        attron(COLOR_PAIR(box_index));
        box(stdscr , 0 , 0);
        attroff(COLOR_PAIR(box_index));

        pthread_mutex_unlock(&IO_Mutex);
    }

    render_play_pause_button();
    render_reset_button();
    render_exit_button();

    print_speed();
    display_coord();
    print_pause_play_state();


    called = true;
    last_diplayed_speed = Speed;
    last_diplayed_coord.x = X_Indent;
    last_diplayed_coord.y = Y_Indent;
    last_diplayed_play_pause_state = Pause;
    
    refresh();

    return NULL;
}