include c_datastructures/makefile $(libs)

PDcurses_Path = C:/msys64/mingw64/lib/pdcurses.a
Linked_List_Path = c_datastructures/bin/
CC = gcc

main:
	make libs
	make objects
	$(CC) -Wall -g3 -o main.exe main.c bin/board_state.o bin/process_state.o bin/render_state.o bin/interface.o bin/input.o -l:pdcurses.a -L$(Linked_List_Path) -llinked_list

objects:
	$(shell mkdir bin)
	$(CC) -c libsrc/process_state.c -o bin/process_state.o
	$(CC) -c libsrc/render_state.c -o bin/render_state.o
	$(CC) -c libsrc/board_state.c -o bin/board_state.o
	$(CC) -c libsrc/interface.c -o bin/interface.o
	$(CC) -c libsrc/input.c -o bin/input.o