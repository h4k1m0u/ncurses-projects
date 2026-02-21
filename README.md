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
