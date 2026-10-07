#include "Board.h"

void Board::intialize_board()
{
    for (int rank = 8; rank >= 1; rank--)
    {
        for (char file = 'a'; file <= 'h'; file++)
        {
            if (rank == 2 or rank == 7)
            {
                if (rank == 2)
                    board[rank][file - 'a' + 1].piece = Piece("pawn", "white");
                else
                    board[rank][file - 'a' + 1].piece = Piece("pawn", "black");
            }
            if (rank == 1 or rank == 8)
            {
                if (rank == 1)
                {
                    if (file == 'a' or file == 'h')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("rook", "white");
                    }
                    if (file == 'b' or file == 'g')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("knight", "white");
                    }
                    if (file == 'c' or file == 'f')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("bishop", "white");
                    }
                    if (file == 'd')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("queen", "white");
                    }
                    if (file == 'e')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("king", "white");
                    }
                }
                else
                {
                    if (file == 'a' or file == 'h')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("rook", "black");
                    }
                    if (file == 'b' or file == 'g')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("knight", "black");
                    }
                    if (file == 'c' or file == 'f')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("bishop", "black");
                    }
                    if (file == 'd')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("queen", "black");
                    }
                    if (file == 'e')
                    {
                        board[rank][file - 'a' + 1].piece = Piece("king", "black");
                    }
                }
            }
        }
    }
}

Board::Board() : board(9, vector<Square>(9))
{
    for (int i = 8; i >= 1; i--)
    {
        for (char c = 'a'; c <= 'h'; c++)
        {
            board[i][c - 'a' + 1] = Square(c, i, Piece());
        }
    }
    intialize_board();
}

bool Board::path_is_clear(char file, int rank, char file_destination, int rank_destination)
{
    int file_direction = 0, rank_direction = 0;
    // horizontal
    if (rank == rank_destination)
    {
        if (file < file_destination)
        {
            file_direction = 1;
        }
        else
        {
            file_direction = -1;
        }
    }
    // vertical
    else if (file == file_destination)
    {
        if (rank < rank_destination)
        {
            rank_direction = 1;
        }
        else
        {
            rank_direction = -1;
        }
    }
    // diagonal
    else
    {
        if (rank < rank_destination)
        {
            rank_direction = 1;
        }
        else
        {
            rank_direction = -1;
        }
        if (file < file_destination)
        {
            file_direction = 1;
        }
        else
        {
            file_direction = -1;
        }
    }

    rank += rank_direction, file += file_direction;
    while (rank != rank_destination or file != file_destination)
    {
        if (board[rank][file - 'a' + 1].piece.type != "")
        {
            return false;
        }

        rank += rank_direction;
        file += file_direction;
    }

    return true;
}