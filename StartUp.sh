#!/bin/sh
StartUp
file="$HOME/cd.sh"
if [ -f "$file" ]; then
    source $file
    rm $file
fi
