#include <iostream>
#include "raylib.h"
#include "Board.h"
#define BOARD_DIMENSION 1000
#define SQUARE_DIMENSION 125
using std::cout;
using std::pair;

int main(void)
{

    InitWindow(BOARD_DIMENSION, BOARD_DIMENSION, "RayChess");

    SetTargetFPS(60);

    Board board;
    pair<char, int> selected_square;
    pair<char, int> destination;
    bool is_square_selected = false;

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Welcome, RayChess!", 190, 200, 20, LIGHTGRAY);

        int rank_increment = 0;
        for (int rank = 8; rank >= 1; rank--)
        {
            int file_increment = 0;
            for (char file = 'a'; file <= 'h'; file++)
            {
                Square s(file, rank, Piece());
                Color color = s.color_detection(rank, file);
                DrawRectangle(file_increment, rank_increment, SQUARE_DIMENSION, SQUARE_DIMENSION, color);
                file_increment += SQUARE_DIMENSION;
                if (board.board[rank][file - 'a' + 1].piece.type != "")
                {
                    DrawTexture(board.board[rank][file - 'a' + 1].piece.texture,
                                file_increment - SQUARE_DIMENSION / 2 - board.board[rank][file - 'a' + 1].piece.texture.width / 2,
                                rank_increment + SQUARE_DIMENSION / 2 - board.board[rank][file - 'a' + 1].piece.texture.height / 2,
                                WHITE);
                }
            }
            rank_increment += SQUARE_DIMENSION;
        }
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();

        char file = char(mouseX / SQUARE_DIMENSION + 'a');
        int rank = 8 - (mouseY / SQUARE_DIMENSION);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!is_square_selected and board.board[rank][file - 'a' + 1].piece.type != "")
            {
                selected_square = std::make_pair(file, rank);
                is_square_selected = true;
            }
            else
            {
                destination = std::make_pair(file, rank);
                board.board[destination.second][destination.first - 'a' + 1].piece =
                    board.board[selected_square.second][selected_square.first - 'a' + 1].piece;
                board.board[selected_square.second][selected_square.first - 'a' + 1].piece.type = "";
                is_square_selected = false;
            }
        }
        if (is_square_selected)
        {
            DrawRectangleLines((selected_square.first - 'a') * SQUARE_DIMENSION,
                               (8 - selected_square.second) * SQUARE_DIMENSION,
                               SQUARE_DIMENSION, SQUARE_DIMENSION, RED);
        }
        EndDrawing();
    }

    CloseWindow();

    return 0;
}