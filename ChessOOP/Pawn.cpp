#include "Pawn.h"

Pawn::Pawn(int colour) : Piece(colour) {};

char Pawn::getSymbol() const {
    return colour == 1 ? 'P' : 'p';
}