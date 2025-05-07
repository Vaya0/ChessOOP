#pragma once
#include "Piece.h"
class King :
    public Piece
{
    King() : Piece() {}
	King(const String& name, bool colour) : Piece(name, colour) {}
};

