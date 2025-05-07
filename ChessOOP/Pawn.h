#pragma once
#include "Piece.h"
class Pawn :
    public Piece
{
    Pawn() : Piece() {}
    Pawn(const String& name, bool colour) : Piece(name, colour) {}
};

