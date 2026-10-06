#!/bin/bash

g++ src/main.cpp src/Square.cpp src/Board.cpp src/Piece.cpp \
    $(pkg-config --cflags --libs raylib) \
    -o raychess && ./raychess