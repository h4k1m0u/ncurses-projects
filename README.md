# How to build & run
```terminal
$ make -j
$ ./build/main
```

# Screenshot
![Screenshot](/screenshots/screenshot.png)

# Platforms
Tested on:
- Ubuntu/Konsole.
- Termux/Android: using [scrcpy][scrcpy]. See steps to [install scrpy][installation-scrcpy] on Linux.

[scrcpy]: https://github.com/Genymobile/scrcpy/blob/master/doc/linux.md#from-an-install-script
[installation-scrcpy]: https://github.com/Genymobile/scrcpy/blob/master/doc/linux.md#from-an-install-script

# Sprite
Mario: [mariouniverse.com][mario]

[mario]: https://www.mariouniverse.com/wp-content/img/sprites/nes/smb/mario-custom.png

# Documentation
## Packages
These packages can be installed with `apt install` (in addition to ncurses):
- `ncurses-example`: /usr/libexec/ncurses-examples/ (source code can be downloaded with `apt-file show ncurses` and found in <ncurses-dir>/`test` folder)
- `ncurses-doc`: /usr/share/doc/ncurses-doc/html/index.html

## Concepts
- **Window:** Data structure describing sub-rectangle (possibly entire) of the screen.
- **Screen:** Subset of a window which is as large as the terminal screen.
    - *curscr:* Screen of what the terminal looks like.
    - *stdscr:* What we want the terminal to look like next (default window used by routines whose names don't start with a 'w', like `refresh()`).
