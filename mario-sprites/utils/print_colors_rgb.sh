#!/usr/bin/env bash
# shades calculated for RED color by utils/calculate_shades.py

case $# in
    0)
      # unicode box
      block_full="\u2588"
      ;;
    1)
      text="$1"
      ;;
    *)
      echo "USAGE: $0 [TEXT]"
      exit 1
      ;;
esac

reds=( 255 255 255 255 255 191 143 107 80 )
greens=( 174 147 111 63 0 0 0 0 0 )
blues=( 174 147 111 63 0 0 0 0 0 )
n_shades=${#reds[@]}

for (( i = 0; i < $n_shades; i++)); do
  r="${reds[$i]}"
  g="${greens[$i]}"
  b="${blues[$i]}"
  # echo -e "\x1b[38;2;${r};${g};${b}m${text}"
  echo -e "\x1b[38;2;${r};${g};${b}m${text:-$block_full}"
done
