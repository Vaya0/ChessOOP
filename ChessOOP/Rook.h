#pragma once
#include "Piece.h"
class Rook :
    public Piece
{
	Rook() : Piece() {}
	Rook(const String& name, bool colour) : Piece(name, colour) {}
};

