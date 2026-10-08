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

Board::Board() : board(9, vector<Square>(9)), white_turn(true)
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

bool Board::move_piece(pair<char, int> selected_square, pair<char, int> destination)
{
    bool is_destination_empty = board[destination.second][destination.first - 'a' + 1].piece.type == "";
    bool opponent = !is_destination_empty and
                    board[destination.second][destination.first - 'a' + 1].piece.color !=
                        board[selected_square.second][selected_square.first - 'a' + 1].piece.color;

    // Pawn legal moves
    if (board[selected_square.second][selected_square.first - 'a' + 1].piece.type == "pawn" and
        board[selected_square.second][selected_square.first - 'a' + 1].piece.pawn_legal_moves(selected_square.first, selected_square.second, destination.first, destination.second, is_destination_empty, opponent))
    {
        if (abs(destination.second - selected_square.second) == 2)
        {
            if (path_is_clear(selected_square.first, selected_square.second, destination.first, destination.second))
            {
                board[destination.second][destination.first - 'a' + 1].piece =
                    board[selected_square.second][selected_square.first - 'a' + 1].piece;
                board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
                return true;
            }
            else
                return false;
        }

        board[destination.second][destination.first - 'a' + 1].piece =
            board[selected_square.second][selected_square.first - 'a' + 1].piece;
        board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
        return true;
    }

    // Rook legal moves
    if (board[selected_square.second][selected_square.first - 'a' + 1].piece.type == "rook" and
        board[selected_square.second][selected_square.first - 'a' + 1].piece.rook_legal_moves(selected_square.first, selected_square.second, destination.first, destination.second, is_destination_empty, opponent) and
        path_is_clear(selected_square.first, selected_square.second, destination.first, destination.second))
    {
        board[destination.second][destination.first - 'a' + 1].piece =
            board[selected_square.second][selected_square.first - 'a' + 1].piece;
        board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
        return true;
    }

    // Knight legal movrs
    if (board[selected_square.second][selected_square.first - 'a' + 1].piece.type == "knight" and
        board[selected_square.second][selected_square.first - 'a' + 1].piece.knight_legal_moves(selected_square.first, selected_square.second, destination.first, destination.second, is_destination_empty, opponent))
    {
        board[destination.second][destination.first - 'a' + 1].piece =
            board[selected_square.second][selected_square.first - 'a' + 1].piece;
        board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
        return true;
    }

    // Bishop legal moves
    if (board[selected_square.second][selected_square.first - 'a' + 1].piece.type == "bishop" and
        board[selected_square.second][selected_square.first - 'a' + 1].piece.bishop_legal_moves(selected_square.first, selected_square.second, destination.first, destination.second, is_destination_empty, opponent) and
        path_is_clear(selected_square.first, selected_square.second, destination.first, destination.second))
    {
        board[destination.second][destination.first - 'a' + 1].piece =
            board[selected_square.second][selected_square.first - 'a' + 1].piece;
        board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
        return true;
    }

    // Queen legal moves
    if (board[selected_square.second][selected_square.first - 'a' + 1].piece.type == "queen" and
        board[selected_square.second][selected_square.first - 'a' + 1].piece.queen_legal_moves(selected_square.first, selected_square.second, destination.first, destination.second, is_destination_empty, opponent) and
        path_is_clear(selected_square.first, selected_square.second, destination.first, destination.second))
    {
        board[destination.second][destination.first - 'a' + 1].piece =
            board[selected_square.second][selected_square.first - 'a' + 1].piece;
        board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
        return true;
    }

    // King legal moves
    if (board[selected_square.second][selected_square.first - 'a' + 1].piece.type == "king" and
        board[selected_square.second][selected_square.first - 'a' + 1].piece.king_legal_moves(selected_square.first, selected_square.second, destination.first, destination.second, is_destination_empty, opponent))
    {
        board[destination.second][destination.first - 'a' + 1].piece =
            board[selected_square.second][selected_square.first - 'a' + 1].piece;
        board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
        return true;
    }
    return false;
}