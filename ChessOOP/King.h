#pragma once
#include "Piece.h"
class King :
    public Piece
{
    King(int colour);

    char getSymbol() const override;
};

