CC = gcc
Data_Structures_Path = c_datastructures/bin/

main: objects deps
	$(CC) -g3 -o conway src/main.c bin/board_state.o bin/process_state.o bin/render_state.o bin/interface.o bin/input.o -lpdcurses -L$(Data_Structures_Path) -llinked_list -ldynamic_array

objects: bin/
	$(CC) -g3 -c src/process_state.c -o bin/process_state.o
	$(CC) -g3 -c src/render_state.c -o bin/render_state.o
	$(CC) -g3 -c src/board_state.c -o bin/board_state.o
	$(CC) -g3 -c src/interface.c -o bin/interface.o
	$(CC) -g3 -c src/input.c -o bin/input.o

deps:
	$(MAKE) -C c_datastructures linked_list
	$(MAKE) -C c_datastructures dynamic_array

bin/:
	$(shell mkdir bin)