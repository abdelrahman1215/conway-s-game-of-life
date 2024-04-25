Linked_List_Path = c_datastructures/bin/
CC = gcc

main:
	$(MAKE) -C c_datastructures linked_list
	$(MAKE) objects
	$(CC) -Wall -g3 -o conway src/main.c bin/board_state.o bin/process_state.o bin/render_state.o bin/interface.o bin/input.o -lpdcurses -L$(Linked_List_Path) -llinked_list

objects:
	$(shell mkdir bin)
	$(CC) -c src/process_state.c -o bin/process_state.o
	$(CC) -c src/render_state.c -o bin/render_state.o
	$(CC) -c src/board_state.c -o bin/board_state.o
	$(CC) -c src/interface.c -o bin/interface.o
	$(CC) -c src/input.c -o bin/input.o