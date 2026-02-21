# Description
Digital clock rendered on the terminal with ncurses.

# How to build & run
First build & install ncurses-utils:

```terminal
$ cd ../ncurses-utils
$ make -j
$ sudo make install
```

Then build the current repo:

```terminal
$ make -j
$ ./build/main
```

# Prerequisites
- ncursesw (ncurses with wide-character support to render UTF8 characters).

# Resources
- [Font Casio fx-7800GC][font]: Copied to `~/.config/GIMP/2.10/fonts` then digitized manually pixel by pixel.

[font]: https://www.wfonts.com/font/casio-fx-7800gc
