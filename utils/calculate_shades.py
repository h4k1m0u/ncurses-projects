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

def darken(channel, factor):
    """ Resulting color becomes darker """
    return int(channel * factor)

def lighten(channel, factor):
    """ Resulting color becomes lighter """
    return int(channel + (255 - channel) * factor)

def calculate_shades(color_rgb: tuple, n: int, factor: float, f) -> list[str]:
    """
    Calculate `n` shades of input `color` by applying given function
    Accord. to function f(), the shades are in ASC. order of darkness (shades) or brightness (tints)
    """
    shades = []
    r, g, b = color_rgb

    for _ in range(n):
        r = f(r, factor)
        g = f(g, factor)
        b = f(b, factor)
        rgb = ( r, g, b )
        shades.append(rgb)

        print(f'color_shade: {r}, {g}, {b}')
        # color_shade = join_rgb(r, g, b)
        # print(f'color_shade: {color_shade}')

    return shades

if __name__ == '__main__':
    # read command-line arguments
    description = 'Calculate n darkened shades of input color'
    help_color = 'Starting color in hex format (e.g. 0xff0000)'
    help_n = f'Number of shades to calculate'

    parser = argparse.ArgumentParser(description=description)
    parser.add_argument('color', help=help_color)
    parser.add_argument('n', type=int, help=help_n)
    args = parser.parse_args()

    color_rgb = split_rgb(args.color)
    lightened_shades = calculate_shades(color_rgb, args.n, 1/4, lighten)
    darkened_shades = calculate_shades(color_rgb, args.n, 3/4, darken)

    shades = lightened_shades[::-1] + [ color_rgb ] + darkened_shades

    print()
    for shade in shades:
        print(f'shade: {shade}')
