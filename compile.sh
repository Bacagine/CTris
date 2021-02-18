#!/bin/bash
# 
# Compile script created by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
# 
# Date: 18/02/2021

# make directories
if [ ! -d "obj" ]; then
    mkdir -p obj/windows
    mkdir -p obj/blocks
fi

if [ ! -d "bin" ]; then
    mkdir bin
fi

# Compile program and organizing the objects files
g++ -c src/main.cpp -o obj/main.o
g++ -c src/windows/*.cpp
mv *.o obj/windows
g++ -c src/blocks/*.cpp
mv *.o obj/blocks
g++ -o bin/ctris obj/*.o obj/windows/*.o obj/blocks/*.o -lncursesw
