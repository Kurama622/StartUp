#!/bin/sh
StartUp
file="/tmp/startup_cd.sh"
if [ -f "$file" ]; then
    source $file
    rm $file
fi
