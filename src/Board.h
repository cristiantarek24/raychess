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
};
