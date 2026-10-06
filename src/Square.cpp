#include "Square.h"
using std::string;

Square::Square(char file, int rank, Piece piece) : file(file), rank(rank), piece(piece) {}
Square::Square() {}

Color Square::color_detection(int rank, char file)
{
    int asci_sum = rank + file;
    return ((asci_sum & 1) ? WHITE : BROWN);
}
