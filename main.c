#include "process.c"
#include <stdio.h>
#include <pdcurses.h>
#include <unistd.h>
#include <time.h>

void print_state(board_state state){
    char frame[state_width][(state_width * 2) + 1] = {{'0'}};
    for(int i = 0 ; i < state_width ; i++){
        frame[i][state_width * 2] = '\n';
    }

    frame[state_width - 1][state_width * 2] = '\000';

    for(int y = 0 ; y < state_width ; y++){
        for(int x = 0 ; x < state_width ; x++){
            frame[y][(x * 2) + 1] = ' ';
            if(state.state[y][x] == 1){
                frame[y][x * 2] = '#';
            }else{
                frame[y][x * 2] = ' ';
            }
        }
    }

    move(0,0);
    printw("%s" , frame);
    refresh();
    struct timespec ts = {.tv_sec = 0 , .tv_nsec = (400 * 1000000)};
    nanosleep(&ts , &ts);
}

int main(){
    initscr();
    clear();

    board_state test = empty_state();
    test.state[7][8] = 1;
    test.state[8][9] = 1;
    test.state[8][10] = 1;
    test.state[9][8] = 1;
    test.state[9][11] = 1;
    test.state[10][9] = 1;
    test.state[10][10] = 1;
    print_state(test);

    nodelay(stdscr , true);
    flushinp();
    for(int i = 0 ; i < 17 ; i++){
        test = new_state(test);
        print_state(test);
        char ch = getch();
        if(ch != ERR){
            return 0;
        }
    }

    endwin();
}