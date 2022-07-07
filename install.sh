#!/bin/bash

mkdir build
cd build
cmake ..
make
cp StartUp /usr/local/bin/ 

