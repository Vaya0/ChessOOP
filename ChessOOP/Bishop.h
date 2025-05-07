#pragma once
#include "Piece.h"
class Bishop :
    public Piece
{
    Bishop(int colour) : Piece(colour) {};

    char getSymbol() const override {
        return colour == 1 ? 'B' : 'b';
    }
};

