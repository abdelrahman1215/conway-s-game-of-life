#include "../headers/globals.h"
#include "../headers/board_state.h"
#include <pdcurses.h>
#include <pthread.h>

void handle_mouse_input(){
    MEVENT event;
    if(nc_getmouse(&event) != OK) return ;

    if(event.x >= play_start_x && event.x <= play_end_x && event.y == play_y){
        if(pause == true){
            pause = false;
        }else{
            pause = true;
        }
    } else if(event.x >= exit_start_x && event.x <= exit_end_x && event.y == exit_y){

        exit(0);
        
    } else if(event.x >= state_start_x && event.y >= state_start_y && event.x <= state_end_x && event.y <= state_end_y){
        lock_state();

        cell_state new_state = alive;
        unsigned x = ((event.x - state_start_x) / 2) + x_indent , y = event.y - state_start_y + y_indent;
        if(lookup_cell_state(board , x , y , false) == alive){
            new_state = dead;
        }

        set_cell(board , x , y , new_state);

        unlock_state();
    }
}

void handle_keyboard_input(int input){
    switch(input){
        case 'q':
        case 'Q':
            exit(0);
            break;

        case ' ':
        case 'p':
        case 'P':
            if(pause == true){
                pause = false;
            }else{
                pause = true;
            }

            break;

        case 'w':
        case 'W':
        case KEY_UP:
            if(y_indent > 0){
                y_indent --;
            }

            break;
        
        case 's':
        case 'S':
        case KEY_DOWN:
            if(y_indent < get_board_height(board) - state_end_y){
                y_indent ++;
            }

            break;

        case 'a':
        case 'A':
        case KEY_LEFT:
            if(x_indent > 0){
                x_indent --;
            }

            break;

        case 'd':
        case 'D':
        case KEY_RIGHT:
            if(x_indent < get_board_width(board) - state_end_x){
                x_indent ++;
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