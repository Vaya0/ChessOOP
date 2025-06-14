#pragma once
#include "Piece.h"
#include "PiecesType.h"
class PieceFactory
{
public:
	static Piece* createFigure(Colour colour, Type); 
};

