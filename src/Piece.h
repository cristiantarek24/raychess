#pragma once
#include <iostream>
#include <string>
#include "raylib.h"
using std::string;

class Piece
{
public:
    string type, color;
    Texture2D texture;

    Piece();
    Piece(string type, string color);

    bool pawn_legal_moves(char file, int rank, char file_destination, int rank_destination, bool is_destination_empty, bool opponent);
};