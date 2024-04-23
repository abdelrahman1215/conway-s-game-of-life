main:
	make libs
	gcc -Wall -g3 -o main.exe main.c -Lbin -lprocess_state -lrender_state -lboard_state -linput -l:pdcurses.a

test:
	gcc -Wall -g3 test.c -o test.exe -l:pdcurses.a

board_state:
	gcc -c src/board_state.c -o bin/board_state.o
	ar rcs bin/libboard_state.a bin/board_state.o dependencies/c_datastructures/bin/liblinked_list.a

process_state:
	gcc -c src/process_state.c -o bin/process_state.o
	ar rcs bin/libprocess_state.a bin/process_state.o bin/libboard_state.a dependencies/c_datastructures/bin/liblinked_list.a

render_state:
	gcc -c src/render_state.c -o bin/render_state.o
	ar rcs bin/librender_state.a bin/render_state.o bin/libprocess_state.a C:/msys64/mingw64/lib/pdcurses.a

input:
	gcc -c src/input.c -o bin/input.o
	ar rcs bin/libinput.a bin/input.o bin/libprocess_state.a C:/msys64/mingw64/lib/pdcurses.a

libs:
	make board_state
	make process_state
	make render_state
	make input
