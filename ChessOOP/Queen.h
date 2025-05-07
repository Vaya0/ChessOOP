#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
    Queen(int colour) : Piece(colour) {};

    char getSymbol() const override {
        return colour == 1 ? 'Q' : 'q';
    }
};

