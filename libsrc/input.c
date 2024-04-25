#include "../headers/globals.h"
#include "../headers/board_state.h"
#include <pdcurses.h>
#include <pthread.h>

void handle_mouse_input(){
    MEVENT event;
    if(nc_getmouse(&event) != OK) return ;

    if(event.x >= Play_Start_X && event.x <= Play_End_X && event.y == Play_Y){

        Pause = !Pause;

    }else if(event.x >= Exit_Start_X && event.x <= Exit_End_X && event.y == Exit_Y){
        exit(0);
    }else if(event.x >= State_Start_X && event.y >= State_Start_Y && event.x <= State_End_X && event.y <= State_End_Y){
        lock_state();

        cell_state new_state = alive;
        unsigned x = ((event.x - State_Start_X) / 2) + X_Indent , y = event.y - State_Start_Y + Y_Indent;
        if(lookup_cell_state(Board , x , y , false) == alive){
            new_state = dead;
        }

        set_cell(Board , x , y , new_state);

        unlock_state();
    }else if(event.x >= Reset_Start_X && event.x <= Reset_End_X && event.y == Reset_Y){
        reset_board(Board);
    }
}

void handle_keyboard_input(int input){
    switch(input){
        case 'q':
        case 'Q':
            exit(0);
            break;

        case ' ':
            Pause = !Pause;

            break;

        case 'w':
        case 'W':
        case KEY_UP:
            if(Y_Indent > 0){
                Y_Indent --;
            }

            break;
        
        case 's':
        case 'S':
        case KEY_DOWN:
            if(Y_Indent < get_board_height(Board) - State_End_Y){
                Y_Indent ++;
            }

            break;

        case 'a':
        case 'A':
        case KEY_LEFT:
            if(X_Indent > 0){
                X_Indent --;
            }

            break;

        case 'd':
        case 'D':
        case KEY_RIGHT:
            if(X_Indent < get_board_width(Board) - State_End_X){
                X_Indent ++;
            }

            break;

        case '.':
            if(Speed < speed_limit){
                pthread_mutex_lock(&Speed_Mutex);

                Speed ++;

                pthread_mutex_unlock(&Speed_Mutex);
            }

            break;

        case ',':
            if(Speed > 1){
                Speed --;
            }

            break;

    }
}

//the purpose of making the function of this type is to be used with pthreads
void *handle_input(void *arg){
    if(stdscr == NULL) return NULL;

    keypad(stdscr , true);
    mousemask(BUTTON1_PRESSED | REPORT_MOUSE_POSITION , NULL);
    noecho();
    int ch = 0;

    while(1){
        ch = getch();

        if(ch == ERR){
            continue;
        }

        if(ch == KEY_MOUSE){
            handle_mouse_input();
        }else{
            handle_keyboard_input(ch);
        }

        flushinp();
    };

    return NULL;
}