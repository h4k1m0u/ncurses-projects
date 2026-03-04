# Rationale
- Export RGB frames images from gimp in `png` format (read with `stb-image`).
- Euclidean distance used to determine the closest palette color, the same way as in the function `map_color()` in `<ncurses-dir>/test/picsmap.c`.

# Prerequisites
- Same [palette][palette] (256 colors) used by `<ncurses-dir>/test/picsmap.c` can be installed to `/usr/share/ncurses-examples/xterm-256color.dat` using:
```terminal
$ sudo apt install ncurses-example
```

[palette]: https://manpages.debian.org/bullseye/xterm/xterm.1.en.html#color0

# Inspiration
Download the source code for ncurses examples (look for this example: `<ncurses-dir>/test/picsmap.c`):
```terminal
$ apt-get source ncurses
```

# Assets
- [Flame][flame]: 96x96px.

[flame]: https://bdragon1727.itch.io/free-effect-bullet-impact-explosion-32x32
