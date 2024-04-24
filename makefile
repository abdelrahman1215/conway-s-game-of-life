PDcurses_Path = C:/msys64/mingw64/lib/pdcurses.a
Linked_List_Path = C:/Users/abder/Desktop/conway\'s/dependencies/c_datastructures/bin/linked_list.o

main:
	make liball
	gcc -Wall -g3 -o main.exe main.c -Lbin -lall -l:pdcurses.a

liball:
	gcc -c libsrc/process_state.c -o bin/process_state.o
	gcc -c libsrc/render_state.c -o bin/render_state.o
	gcc -c libsrc/board_state.c -o bin/board_state.o
	gcc -c libsrc/interface.c -o bin/interface.o
	gcc -c libsrc/input.c -o bin/input.o
	ar rcs bin/liball.a bin/board_state.o bin/process_state.o bin/render_state.o bin/input.o bin/interface.o $(Linked_List_Path) $(PDcurses_Path)