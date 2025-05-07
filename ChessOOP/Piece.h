#pragma once

class Piece
{
	public:
		Piece(int colour) : colour(colour) {}
		virtual ~Piece() {};
		virtual char getSymbol() const = 0;

	protected:
	int colour; // 1 - white, 2 - black	
};

