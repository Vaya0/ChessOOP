#pragma once
#include "Piece.h"

class Bishop :
    public Piece
{
public:
    Bishop(int colour);

    char getSymbol() const override;
};

