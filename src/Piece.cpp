#include "Piece.h"

Piece::Piece() : type(""), color("") {}
Piece::Piece(string type, string color) : type(type), color(color)
{
    string imagePath = "pieces/" + color + "/" + type + ".png";
    Image img = LoadImage(imagePath.c_str());
    texture = LoadTextureFromImage(img);
    UnloadImage(img);
}

bool Piece::pawn_legal_moves(char file, int rank, char file_destination, int rank_destination, bool is_destination_empty, bool opponent)
{
    if (!opponent and file != file_destination)
        return false;

    if (is_destination_empty)
    {
        if (this->color == "white" and (rank + 1 == rank_destination or (rank + 2 == rank_destination and rank == 2)))
        {
            return true;
        }
        else if (this->color == "black" and (rank - 1 == rank_destination or (rank - 2 == rank_destination and rank == 7)))
        {
            return true;
        }
    }
    else
    {
        if (!opponent)
            return false;

        if (this->color == "white" and rank + 1 == rank_destination and (file - 1 == file_destination or file + 1 == file_destination))
        {
            return true;
        }
        else if (this->color == "black" and rank - 1 == rank_destination and (file - 1 == file_destination or file + 1 == file_destination))
        {
            return true;
        }
    }

    return false;
}

bool Piece::rook_legal_moves(char file, int rank, char file_destination, int rank_destination, bool is_destination_empty, bool opponent)
{
    if ((file == file_destination and rank != rank_destination) or (rank == rank_destination and file != file_destination))
    {
        if (is_destination_empty or (!is_destination_empty and opponent))
        {
            return true;
        }
    }
    return false;
}