# Platforms
Tested on:
- Ubuntu: Konsole (KDE Plasma) & Console (Gnome).
- Termux/Android: using [scrcpy][scrcpy]. See steps to [install scrpy][installation-scrcpy] on Linux.

[scrcpy]: https://github.com/Genymobile/scrcpy/blob/master/doc/linux.md#from-an-install-script
[installation-scrcpy]: https://github.com/Genymobile/scrcpy/blob/master/doc/linux.md#from-an-install-script

# Libraries
`stb-utils` and `ncurses-utils` (in this order) should be installed on Termux/Android by overriding the `prefix` variable as follows:

```terminal
$ pkg install binutils  # provides gar (GNU ar)
$ cd $PREFIX/bin
$ ln -s gar ar
$ make prefix=$PREFIX install
```

While on linux, `prefix` is already set in the Makefile:

```terminal
$ sudo make install
```

# Prerequisites
- ncursesw (ncurses with wide-character support to render UTF8 characters).

# Documentation
## Packages
These packages can be installed with `apt install` (in addition to ncurses):
- `ncurses-example`: /usr/libexec/ncurses-examples/ (source code for ncurses can be downloaded with `apt-get source ncurses`, then examples can be found in <ncurses-dir>/`test` folder)
- `ncurses-doc`: /usr/share/doc/ncurses-doc/html/index.html

## Concepts
- **Window:** Data structure describing sub-rectangle (possibly entire) of the screen.
- **Screen:** Subset of a window which is as large as the terminal screen.
    - *curscr:* Screen of what the terminal looks like.
    - *stdscr:* What we want the terminal to look like next (default window used by routines whose names don't start with a 'w', like `refresh()`).
