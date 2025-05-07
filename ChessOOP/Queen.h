#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
public:
    Queen(int colour);

    char getSymbol() const override;
};

