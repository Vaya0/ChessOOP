#pragma once
#include "Piece.h"
class Queen :
    public Piece
{
	Queen() : Piece() {}
	Queen(const String& name, bool colour) : Piece(name, colour) {}
};

