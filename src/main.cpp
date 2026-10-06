#include <iostream>
#include "raylib.h"
#include "Board.h"
#define BOARD_DIMENSION 1000
#define SQUARE_DIMENSION 125
using std::cout;

int main(void)
{

    InitWindow(BOARD_DIMENSION, BOARD_DIMENSION, "RayChess");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Welcome, RayChess!", 190, 200, 20, LIGHTGRAY);
        Board board;
        
        int rank_increment = 0;
        for (int rank = 8; rank >= 1; rank--)
        {
            int file_increment = 0;
            for (char file = 'a'; file <= 'h'; file++)
            {
                Square s(rank, file, Piece());
                Color color = s.color_detection(rank, file);
                DrawRectangle(file_increment, rank_increment, SQUARE_DIMENSION, SQUARE_DIMENSION, color);
                file_increment += SQUARE_DIMENSION;
                if(board.board[rank][file - 'a' + 1].piece.type != "")
                {
                    DrawTexture(board.board[rank][file - 'a' + 1].piece.texture, file_increment - SQUARE_DIMENSION/2 - board.board[rank][file - 'a' + 1].piece.texture.width/2, rank_increment + SQUARE_DIMENSION/2 - board.board[rank][file - 'a' + 1].piece.texture.height/2, WHITE);
                }
            }
            rank_increment += SQUARE_DIMENSION;
        }
        

        EndDrawing();
    }

    CloseWindow();

    return 0;
}