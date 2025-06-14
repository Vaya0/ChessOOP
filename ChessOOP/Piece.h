#pragma once
#include "PiecesType.h"
class Board;

class Piece
{
	public:
		Piece(Colour colour, Type type) : colour(colour), type(type) {}
		virtual ~Piece() {};
		virtual Piece* clone() const = 0;
		virtual wchar_t getSymbol() const = 0;
		Colour getColor() const { return colour; }
		Type getType() const { return type; }
		virtual bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const = 0;

	protected:
	Colour colour; // white, black
	Type type; // Type of the piece (Pawn, Rook, Knight, etc.)	
};

