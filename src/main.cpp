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
    pair<char, int> white_king;
    pair<char, int> black_king;
    pair<char, int> king_pos = board.white_turn ? white_king : black_king;

    bool is_square_selected = false;
    bool promotion_pending = false;
    bool checked = false;
    pair<char, int> promotion_square;
    const vector<string> pormotion_pieces = {"queen", "rook", "bishop", "knight"};
    vector<Piece> black_pormotion(4), white_pormotion(4);
    int i = 0;
    for (auto &p : black_pormotion)
    {
        p = Piece(pormotion_pieces[i++], "black");
    }
    i = 0;
    for (auto &p : white_pormotion)
    {
        p = Piece(pormotion_pieces[i++], "white");
    }

    while (!WindowShouldClose())
    {

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Welcome, RayChess!", 190, 200, 20, LIGHTGRAY);

        // King Check
        for (int rank = 1; rank <= 8; rank++)
        {
            for (char file = 'a'; file <= 'h'; file++)
            {
                Piece &piece = board.board[rank][file - 'a' + 1].piece;

                if (piece.type == "king")
                {
                    if (piece.color == "white")
                        white_king = {file, rank};
                    else
                        black_king = {file, rank};
                }
            }
        }

        king_pos = board.white_turn ? white_king : black_king;

        // Rendring the board
        int rank_increment = 0;
        for (int rank = 8; rank >= 1; rank--)
        {
            int file_increment = 0;
            for (char file = 'a'; file <= 'h'; file++)
            {
                Square s(file, rank, Piece());
                Color color = s.color_detection(rank, file);
                DrawRectangle(file_increment, rank_increment, SQUARE_DIMENSION, SQUARE_DIMENSION, color);

                // Highlighting the valid squares
                if (is_square_selected and board.valid_move(selected_square, std::make_pair(file, rank), king_pos))
                {
                    bool is_capture = board.board[rank][file - 'a' + 1].piece.type != "";
                    Color highlight = (is_capture ? Color{220, 50, 50, 120}
                                                  : Color{0, 200, 0, 100});
                    DrawRectangle(file_increment, rank_increment,
                                  SQUARE_DIMENSION, SQUARE_DIMENSION,
                                  highlight);
                }

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

        checked = (board.check(white_king) or board.check(black_king));

        if (!promotion_pending and IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (!is_square_selected) // select the piece
            {
                if (((board.board[rank][file - 'a' + 1].piece.color == "white" and board.white_turn) or
                     (board.board[rank][file - 'a' + 1].piece.color == "black" and !board.white_turn)) and
                    board.board[rank][file - 'a' + 1].piece.type != "")
                {
                    selected_square = std::make_pair(file, rank);
                    is_square_selected = true;
                }
            }
            // if selected same color piece
            else if (is_square_selected and
                     board.board[rank][file - 'a' + 1].piece.type != "" and
                     board.board[rank][file - 'a' + 1].piece.color ==
                         board.board[selected_square.second][selected_square.first - 'a' + 1].piece.color)
            {
                selected_square = std::make_pair(file, rank);
                is_square_selected = true;
            }

            else // move to destination
            {
                destination = std::make_pair(file, rank);

                if (board.valid_move(selected_square, destination, king_pos))
                {
                    board.move_piece_to_destination(selected_square, destination);
                    board.white_turn = !board.white_turn;

                    if (board.board[destination.second][destination.first - 'a' + 1].piece.type == "pawn")
                    {
                        if (destination.second == 1)
                        {

                            promotion_pending = true;
                            promotion_square = destination;
                        }
                        else if (destination.second == 8)
                        {
                            promotion_pending = true;
                            promotion_square = destination;
                        }
                    }
                }
                is_square_selected = false;
            }
        }

        if (promotion_pending)
        {
            DrawRectangle(250, 400, 500, 200, DARKGRAY);
            DrawText("Choose promotion: ", 350, 420, 25, WHITE);
            int posX = 260, posY = 450, inc = 115;
            Vector2 mouse = GetMousePosition();
            vector<Rectangle> rec(4);
            vector<Piece> &promotion = (board.board[promotion_square.second][promotion_square.first - 'a' + 1].piece.color ==
                                                "white"
                                            ? white_pormotion
                                            : black_pormotion);
            int idx = 0;
            for (auto &p : promotion)
            {
                DrawTexture(p.texture, posX, posY, WHITE);
                rec[idx].height = p.texture.height + 5;
                rec[idx].width = p.texture.width + 5;
                rec[idx].x = posX;
                rec[idx].y = posY;
                posX += inc, idx++;
            }
            for (int i = 0; i <= 3; i++)
            {
                if (CheckCollisionPointRec(mouse, rec[i]) and IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    UnloadTexture(board.board[promotion_square.second][promotion_square.first - 'a' + 1].piece.texture);
                    board.board[promotion_square.second][promotion_square.first - 'a' + 1].piece =
                        Piece(pormotion_pieces[i], board.board[promotion_square.second][promotion_square.first - 'a' + 1].piece.color);
                    promotion_pending = false;
                    break;
                }
            }
        }

        if (board.stale_mate(king_pos) or board.check_mate(king_pos))
        {
            cout << "Game Over\n";
        }
        // highlighting selected square
        if (is_square_selected)
        {
            DrawRectangleLines((selected_square.first - 'a') * SQUARE_DIMENSION,
                               (8 - selected_square.second) * SQUARE_DIMENSION,
                               SQUARE_DIMENSION, SQUARE_DIMENSION, RED);
        }

        EndDrawing();
    }

    for (auto &p : black_pormotion)
    {
        UnloadTexture(p.texture);
    }

    for (auto &p : white_pormotion)
    {
        UnloadTexture(p.texture);
    }

    for (int r = 8; r >= 1; r--)
    {
        for (char f = 'a'; f <= 'h'; f++)
        {
            if (board.board[r][f - 'a' + 1].piece.type != "")
                UnloadTexture(board.board[r][f - 'a' + 1].piece.texture);
        }
    }

    CloseWindow();

    return 0;
}