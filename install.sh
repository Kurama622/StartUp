#!/bin/bash
if which xmake >/dev/null 2>&1; then
    xmake build
    sudo xmake install
else
    if [ ! -d "build" ]; then
        mkdir build
    fi
    cd build
    if [ ! -f "Makefile" ]; then
        cmake ..
    fi
    make
    sudo cp StartUp /usr/local/bin/ 
fi

