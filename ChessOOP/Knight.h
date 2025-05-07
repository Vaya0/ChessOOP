#pragma once
#include "Piece.h"
class Knight :
    public Piece
{
public:
    Knight(int colour);

    char getSymbol() const override;
};

