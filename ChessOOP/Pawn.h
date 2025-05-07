#pragma once
#include "Piece.h"
class Pawn :
    public Piece
{
    Pawn(int colour);

    char getSymbol() const override;
};

