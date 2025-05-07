#include "Board.h"

Board::Board() {
	initializeBoard();
}
Board::~Board() {

}
void Board::initializeBoard() {

	//white pieces
	field[7][0].setName("Rook");
	field[7][0].setColour("1");
	field[7][1].setName("Knight");
	field[7][1].setColour("1");
	field[7][2].setName("Bishop");
	field[7][2].setColour("1");
	field[7][3].setName("Queen");
	field[7][3].setColour("1");
	field[7][4].setName("King");
	field[7][4].setColour("1");
	field[7][5].setName("Bishop");
	field[7][5].setColour("1");
	field[7][6].setName("Kight");
	field[7][6].setColour("1");
	field[7][7].setName("Rook");
	field[7][7].setColour("1");

	field[6][0].setName("Pawn");
	field[6][0].setColour("1");
	field[6][1].setName("Pawn");
	field[6][1].setColour("1");
	field[6][2].setName("Pawn");
	field[6][2].setColour("1");
	field[6][3].setName("Pawn");
	field[6][3].setColour("1");
	field[6][4].setName("Pawn");
	field[6][4].setColour("1");
	field[6][5].setName("Pawn");
	field[6][5].setColour("1");
	field[6][6].setName("Pawn");
	field[6][6].setColour("1");
	field[6][7].setName("Pawn");
	field[6][7].setColour("1");

	//black pieces
	field[0][0].setName("Rook");
	field[0][0].setColour("2");
	field[0][1].setName("Knight");
	field[0][1].setColour("2");
	field[0][2].setName("Bishop");
	field[0][2].setColour("2");
	field[0][3].setName("Queen");
	field[0][3].setColour("2");
	field[0][4].setName("King");
	field[0][4].setColour("2");
	field[0][5].setName("Bishop");
	field[0][5].setColour("2");
	field[0][6].setName("Knight");
	field[0][6].setColour("2");
	field[0][7].setName("Rook");
	field[0][7].setName("2");

	field[1][0].setName("Pawn");
	field[1][0].setColour("2");
	field[1][1].setName("Pawn");
	field[1][1].setColour("2");
	field[1][2].setName("Pawn");
	field[1][2].setColour("2");
	field[1][3].setName("Pawn");
	field[1][3].setColour("2");
	field[1][4].setName("Pawn");
	field[1][4].setColour("2");
	field[1][5].setName("Pawn");
	field[1][5].setColour("2");
	field[1][6].setName("Pawn");
	field[1][6].setColour("2");
	field[1][7].setName("Pawn");
	field[1][7].setColour("2");
}
