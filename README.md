this is an implementation of conway's game of life written in c

game controls:
* q or exit button -> quit
* space or play/pause button -> play/pause
* arrow keys or wasd -> move around the board
* , and . -> decrease and increase speed
* reset button -> reset the board

how to build the project :
* before building the project make sure to install pdcurses and pthreads (if you are on windows) 
* [pdcurses] (https://sourceforge.net/projects/pdcurses/)

* then you just have to edit the CC variable in the makefile of the project and the c_datastructures submodule into what ever compiler you use

* then just:
```
make
```