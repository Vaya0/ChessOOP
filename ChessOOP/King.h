#pragma once
#include "Piece.h"
class King :
    public Piece
{
public:
    King(int colour);

    char getSymbol() const override;
};

