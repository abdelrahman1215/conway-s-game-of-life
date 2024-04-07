main:
	gcc -Wall -g3 -o main.exe main.c -Lbin -lboard_state

board_state:
	gcc -c src/board_state.c -o bin/board_state.o
	ar rcs bin/libboard_state.a bin/board_state.o dependencies/c_datastructures/bin/linked_list.o

process:
	gcc -c src/process.c -o bin/process.o
	ar rcs bin/libprocess.a bin/process.o bin/board_state.o dependencies/c_datastructures/bin/linked_list.o