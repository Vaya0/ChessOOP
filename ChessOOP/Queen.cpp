#include "Queen.h"

Queen::Queen(int colour) : Piece(colour) {};

char Queen::getSymbol() const  {
    return colour == 1 ? 'Q' : 'q';
}
