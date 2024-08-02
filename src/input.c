#include "../headers/globals.h"
#include "../headers/interface.h"
#include "../headers/board_state.h"
#include "../headers/render_state.h"
#include <ncursesw/curses.h>
#include <pthread.h>

void quit(){
    keypad(stdscr , false);
    endwin();
    printf("\033[?1003l\n");
    exit(0);
}

void handle_mouse_input(int ch){
    MEVENT event;
    static int Last_X = -1 , Last_Y = -1;

    if(getmouse(&event) != OK) return ;

    if(event.x != Last_X || event.y != Last_Y){
        unhighlight_exit_button();
        unhighlight_play_pause_button();
        unhighlight_reset_button();
        unhighlight_cells();

        if(event.x >= Play_Start_X && event.x <= Play_End_X && event.y == Play_Y){
            highlight_play_pause_button();
        }else if(event.x >= Exit_Start_X && event.x <= Exit_End_X && event.y == Exit_Y){
            highlight_exit_button();
        }else if(event.x >= State_Start_X && event.y >= State_Start_Y && event.x <= State_End_X && event.y <= State_End_Y ){
            unsigned x = (event.x - State_Start_X) / 2 , y = event.y - State_Start_Y;
            highlight_cell(x , y);

            render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);
            refresh();
        }else if(event.x >= Reset_Start_X && event.x <= Reset_End_X && event.y == Reset_Y){
            highlight_reset_button();
        }
    }

    Last_X = event.x;
    Last_Y = event.y;

    if(ch != KEY_MOUSE) return ;

    if(event.x >= Play_Start_X && event.x <= Play_End_X && event.y == Play_Y){
        Pause = !Pause;
    }else if(event.x >= Exit_Start_X && event.x <= Exit_End_X && event.y == Exit_Y){
        quit();
    }else if(event.x >= State_Start_X && event.y >= State_Start_Y && event.x <= State_End_X && event.y <= State_End_Y ){
        lock_state();
        cell_state new_state = alive;
        unsigned x = ((event.x - State_Start_X) / 2) + X_Indent , y = event.y - State_Start_Y + Y_Indent;
        if(lookup_cell_state(Board , x , y , false) == alive){
            new_state = dead;
        }
        set_cell(Board , x , y , new_state);
        unlock_state();

        render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);
        refresh();
    }else if(event.x >= Reset_Start_X && event.x <= Reset_End_X && event.y == Reset_Y){
        reset_board(Board);
    }
}

void handle_keyboard_input(int input){
    switch(input){
        case 'q':
        case 'Q':
            quit();
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

            render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);
            refresh();

            break;
        
        case 's':
        case 'S':
        case KEY_DOWN:
            if(Y_Indent < get_board_height(Board) - State_End_Y){
                Y_Indent ++;
            }

            render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);
            refresh();

            break;

        case 'a':
        case 'A':
        case KEY_LEFT:
            if(X_Indent > 0){
                X_Indent --;
            }

            render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);
            refresh();

            break;

        case 'd':
        case 'D':
        case KEY_RIGHT:
            if(X_Indent < get_board_width(Board) - State_End_X){
                X_Indent ++;
            }

            render_state(Board , stdscr , State_Start_X , State_Start_Y , State_End_X , State_End_Y);
            refresh();

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

    int ch = 0;

    ch = getch();

    handle_mouse_input(ch);
    
    if(ch == ERR){
        return NULL;
    }

    if(ch != KEY_MOUSE){
        handle_keyboard_input(ch);
    }

    flushinp();

    return NULL;
}