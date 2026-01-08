#!/usr/bin/env python3
# Equations to calcuate shades & tints: https://stackoverflow.com/q/6615002/2228912
import argparse

def split_rgb(color: str) -> tuple:
    color_base10 = int(color, 16)
    r = color_base10 >> 16
    g = (color_base10 >> 8) & 0xff
    b = color_base10 & 0xff

    return r, g, b

def join_rgb(r: int, g: int, b: int) -> str:
    r_hex = hex(r)[2:]
    g_hex = hex(g)[2:]
    b_hex = hex(b)[2:]
    color = f'0x{r_hex:02}{g_hex:02}{b_hex:02}'

    return color

def calculate_shades(color: str, n_shades: int, factor: float) -> list:
    """Calculate `n_shades` darkened shades of input `color` (adding black)"""
    r, g, b = split_rgb(color)

    for _ in range(n_shades):
        r = int(r * factor)
        g = int(g * factor)
        b = int(b * factor)
        color_shade = join_rgb(r, g, b)
        print(f'color_shade: {color_shade}')

def calculate_tints(color: str, n_tints: int, factor: float) -> list:
    """Calculate `n_tints` lightend shades of input `color` (adding white)"""
    r, g, b = split_rgb(color)

    for _ in range(n_tints):
        r = int(r + (255 - r) * factor)
        g = int(g + (255 - g) * factor)
        b = int(b + (255 - b) * factor)
        color_shade = join_rgb(r, g, b)
        print(f'color_tint: {color_shade}')

if __name__ == '__main__':
    # read command-line arguments
    description = 'Calculate n darkened shades of input color'
    help_color = 'Starting color in hex format (e.g. 0xff0000)'
    help_n = f'Number of shades to calculate'

    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('color', help=help_color)
    parser.add_argument('n', type=int, help=help_n)
    args = parser.parse_args()

    print('Shades:')
    calculate_shades(args.color, args.n, 3/4)
    print('Tints:')
    calculate_tints(args.color, args.n, 1/4)
