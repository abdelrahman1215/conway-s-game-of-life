#include "../headers/process_state.h"
#include "../headers/render_state.h"
#include "../headers/board_state.h"
#include "../headers/interface.h"
#include "../headers/globals.h"
#include "../headers/input.h"

#include <pdcurses.h>
#include <assert.h>
#include <time.h>



void *render_board(void *){
    Speed = 2;
    const int nano_per_sec = 1000000000;
    struct timespec spec = {.tv_nsec =  nano_per_sec / Speed, .tv_sec = 0};

    while(1){
        render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);

        if(Pause == false){
            pthread_mutex_lock(&Speed_Mutex);
            if(Speed == 1){
                spec.tv_sec = 1;
                spec.tv_nsec = 0;
            }else{
                spec.tv_sec = 0;
                spec.tv_nsec = (nano_per_sec / Speed) - (nano_per_sec / 100);
            }
            pthread_mutex_unlock(&Speed_Mutex);
            
            nanosleep(&spec , NULL);
            
            //checks if the the game is still playing after the sleeping period
            if(Pause == false){
                update_board_state(Board);
            }
        }

        spec.tv_nsec = nano_per_sec / 100;

        nanosleep(&spec , NULL);

        refresh();
    }
}

int main(){
    pthread_mutex_init(&IO_Mutex , NULL);
    pthread_mutex_init(&Speed_Mutex , NULL);

    Pause = true;

    printf("\033[?1003h\n");

    initscr();

    start_color();
    keypad(stdscr , true);
    mousemask(BUTTON1_PRESSED | BUTTON1_CLICKED | BUTTON1_DOUBLE_CLICKED | REPORT_MOUSE_POSITION , NULL);
    mouseinterval(0);
    noecho();
    refresh();
    curs_set(0);
    nodelay(stdscr , true);

    attron(COLOR_PAIR(box_index));
    box(stdscr , 0 , 0);
    attron(COLOR_PAIR(box_index));

    Win_Width = getmaxx(stdscr) ;
    Win_Height = getmaxy(stdscr);

    Board = new_board_state(Win_Height * 3 , Win_Width * 3);

    X_Indent = Win_Width;
    Y_Indent = Win_Height;

    State_Start_X = 2;
    State_Start_Y = 1;

    State_End_X = Win_Width - 1;
    State_End_Y = Win_Height - 2;

    init_pair(button_index , COLOR_CYAN , COLOR_BLACK);
    init_pair(box_index , COLOR_BLUE , COLOR_BLACK);
    init_pair(button_highlight_index , COLOR_BLACK , COLOR_BLUE);
    init_pair(cell_highlight_index , COLOR_BLACK , COLOR_WHITE);

    pthread_t render_thread;
    pthread_create(&render_thread , NULL , render_board , NULL );

    while(1){
        handle_input(NULL);
        render_interface(NULL);
    }

    endwin();


    destroy_board_state(Board);
}
