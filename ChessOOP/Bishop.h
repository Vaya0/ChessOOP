#pragma once
#include "Piece.h"
class Bishop :
    public Piece
{
	Bishop() : Piece() {}
	Bishop(const String& name, bool colour) : Piece(name, colour) {}
};

