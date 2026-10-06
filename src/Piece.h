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
};