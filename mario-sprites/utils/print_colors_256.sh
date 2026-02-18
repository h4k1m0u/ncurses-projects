#!/usr/bin/env bash
usage() {
  cat << HEREDOC
Print shell's palette of 256 colors
USAGE: $0 [-n] [-b] [-t TEXT] [-d DELIMITER]
Text: to print for each color
Delimiter: to print between each text
-n: Set text to a color index for each color
-b: Set text to box
HEREDOC
}

print_indexes="1"
text=""
delimiter=" "

while getopts "t:d:nbh" arg; do
  case $arg in
    n)
      print_indexes=0
      ;;
    b)
      text="\u2588"
      ;;
    h)
      usage
      exit 0
      ;;
    t)
      text="$OPTARG"
      ;;
    d)
      delimiter="$OPTARG"
      ;;
    *)
      usage
      exit 1
      ;;
  esac
done

shift $(( OPTIND - 1 ))

if [[ "$print_indexes" -ne 0 && -z "$text" ]]; then
  echo "Text not set"
  exit 1
fi

for i in {0..255}; do
  [ "$print_indexes" -eq 0 ] && text="$i"
  echo -ne "\x1b[38;5;${i}m${text}${delimiter}"
done

echo
