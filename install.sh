#!/bin/bash

if [ ! -d "build" ]; then
    mkdir build
fi
cd build
if [ ! -f "Makefile" ]; then
    cmake ..
    make
else
    make
fi
sudo cp StartUp /usr/local/bin/ 

