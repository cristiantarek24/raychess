#!/bin/bash

g++ src/main.cpp src/Square.cpp src/Board.cpp \
    $(pkg-config --cflags --libs raylib) \
    -o raychess && ./raychess