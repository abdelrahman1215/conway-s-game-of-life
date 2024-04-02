main:
	gcc -Wall -g3 -o main.exe main.c -l:pdcurses.a

board_state:
	gcc -c src/board_state.c -o bin/board_state.o -Ldependencies/c_datastructures/bin/ -llinked_list
	ar rcs bin/libboard_state.a bin/board_state.o
	del bin/board_state.o
