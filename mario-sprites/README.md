# Description
Animated Mario sprite rendered on the terminal with ncurses.

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

# Screenshot
![Screenshot](screenshots/screenshot.png)

# Platforms
Tested on:
- Ubuntu/Konsole.
- Termux/Android: using [scrcpy][scrcpy]. See steps to [install scrpy][installation-scrcpy] on Linux.

[scrcpy]: https://github.com/Genymobile/scrcpy/blob/master/doc/linux.md#from-an-install-script
[installation-scrcpy]: https://github.com/Genymobile/scrcpy/blob/master/doc/linux.md#from-an-install-script

# Sprite
Mario: [mariouniverse.com][mario]

[mario]: https://www.mariouniverse.com/wp-content/img/sprites/nes/smb/mario-custom.png
