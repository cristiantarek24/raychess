#pragma once
#include "Piece.h"
#include "raylib.h"

class Square{
public:    
    char file;
    int rank;
    Piece* piece;

    Square(char file, int rank, Piece* piece = nullptr);
    Square();

    Color color_detection(int rank , char file);
};