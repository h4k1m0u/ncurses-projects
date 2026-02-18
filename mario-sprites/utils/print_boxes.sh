#!/usr/bin/env bash

case $# in
  0)
    rows="10"
    ;;
  1)
    rows="$1"
    ;;
  *)
    echo "USAGE: $0 [ROWS]"
    exit 1
    ;;
esac

# unicode boxes
block_full="\u2588"
block_dark_shade="\u2593"
block_medium_shade="\u2592"
block_light_shade="\u2591"

for i in $( seq "$rows"); do
  echo -e "$block_full$block_dark_shade$block_medium_shade$block_light_shade"
done
