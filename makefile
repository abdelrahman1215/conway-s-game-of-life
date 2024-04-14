main:
	make libs
	gcc -Wall -g3 -o main.exe main.c -Lbin -lprocess_state -lrender_state -lboard_state -l:pdcurses.a

board_state:
	gcc -c src/board_state.c -o bin/board_state.o
	ar rcs bin/libboard_state.a bin/board_state.o dependencies/c_datastructures/bin/liblinked_list.a

process_state:
	gcc -c src/process_state.c -o bin/process_state.o
	ar rcs bin/libprocess_state.a bin/process_state.o bin/libboard_state.a

render_state:
	gcc -c src/render_state.c -o bin/render_state.o
	ar rcs bin/librender_state.a bin/render_state.o bin/libprocess_state.a

libs:
	make board_state
	make process_state
	make render_state