#!/bin/bash

mkdir -p build
cd build
cmake ..
make
sudo cp StartUp /usr/local/bin/ 
