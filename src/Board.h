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
    bool is_leagal_move(pair<char, int> selected_square, pair<char, int> destination);
    bool check(pair<char, int> pos);
    bool valid_move(pair<char, int> selected_square, pair<char, int> destination, pair<char, int> pos);
    bool check_mate(pair<char, int> king_pos);
    bool stale_mate(pair<char, int> king_pos);
};
