#include "Piece.h"

Piece::Piece() : type(""), color("") {}
Piece::Piece(string type, string color) : type(type), color(color)
{
    string imagePath = "pieces/" + color + "/" + type + ".png";
    Image img = LoadImage(imagePath.c_str());
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}