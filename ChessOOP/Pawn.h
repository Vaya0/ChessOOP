#pragma once
#include "Piece.h"
#include "PiecesType.h"

class Pawn :
    public Piece
{
public:
    Pawn(Colour colour);
    Piece* clone() const override;
    wchar_t getSymbol() const override;
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol, const Board& board) const override;

};

