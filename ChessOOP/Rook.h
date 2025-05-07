#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
public:
	Rook(int colour);

    char getSymbol() const override;
};

