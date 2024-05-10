this is an implementation of conway's game of life written in c

game controls:
* q or exit button -> quit
* space or play/pause button -> play/pause
* arrow keys or wasd -> move around the board
* , and . -> decrease and increase speed
* reset button -> reset the board

cloning :

* for windows :
```
git clone --recursive https://github.com/abdelrahman1215/conway-s-game-of-life.git
```

* for linux
```
git clone --recursive -b ncursesw https://github.com/abdelrahman1215/conway-s-game-of-life.git
```

building :

* before building install
    * for windows [pdcurses](https://sourceforge.net/projects/pdcurses/) and [pthreads](https://sourceforge.net/projects/pthreads4w/)
    * for linux ncurses and ncursesw

* then edit the CC variable in the makefile of the project and the c_datastructures submodule into what ever compiler you use

* then just:
```
make
```