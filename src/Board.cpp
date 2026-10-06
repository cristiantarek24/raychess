#include "Board.h"


Board::Board() : board(9, vector<Square>(9)){
    for(int i = 8; i >= 1; i --){
        for(char c = 'a'; c <= 'h'; c ++){
            board[i][c - 'a' + 1] = Square(c , i);
        }
    }
}