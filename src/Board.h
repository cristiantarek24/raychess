#pragma once

#include "Square.h"
#include <vector>
using std::vector;

class Board
{
public:
    vector<vector<Square>> board;
    Board();

    void intialize_board();
    bool path_is_clear(char file, int rank, char file_destination, int rank_destination);
};
