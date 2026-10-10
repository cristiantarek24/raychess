#pragma once

#include "Square.h"
#include <vector>
#include <utility>
using std::pair;
using std::vector;

class Board
{
public:
    vector<vector<Square>> board;
    Board();
    bool white_turn;

    void intialize_board();
    bool path_is_clear(char file, int rank, char file_destination, int rank_destination);
    bool move_piece(pair<char, int> source, pair<char, int> destination);
    void move_piece_to_destination(pair<char, int> selected_square, pair<char, int> destination);
};
