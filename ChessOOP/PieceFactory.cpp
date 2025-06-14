#include "PieceFactory.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Rook.h"
#include "Queen.h"
#include "Pawn.h"



Piece* PieceFactory::createFigure(Colour colour, Type type)
{

	switch (type)
	{
	case Type::KING:
		return new King(colour);
	case Type::QUEEN:
		return new Queen(colour);
	case Type::KNIGHT:
		return new Knight(colour);
	case Type::BISHOP:
		return new Bishop(colour);
	case Type::PAWN:
		return new  Pawn(colour);
	case Type::ROOK:
		return new Rook(colour);
	}
}
