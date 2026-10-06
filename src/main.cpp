#include<iostream>
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
            for(int rank = 8; rank >= 1; rank --){
                int file_increment = 0;
                for(char file = 'a'; file <= 'h'; file ++){
                    Square s(rank , file);
                    Color color = s.color_detection(rank , file);
                    DrawRectangle(file_increment, rank_increment, SQUARE_DIMENSION, SQUARE_DIMENSION, color);
                    file_increment += 125;
                }
                rank_increment += 125;
            }

        EndDrawing();
        
    }

    
    
    CloseWindow();        

    return 0;
}