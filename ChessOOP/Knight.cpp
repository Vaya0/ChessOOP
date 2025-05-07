#include "Knight.h"

Knight::Knight(int colour) : Piece(colour) {};

char Knight::getSymbol() const {
    return colour == 1 ? 'N' : 'n';
}
