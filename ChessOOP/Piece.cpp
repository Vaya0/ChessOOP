#include "Piece.h"

Piece::Piece() {
	name = "";
	colour = 0;
}
Piece::Piece(const String& name, bool colour) : name(name){}

void Piece::setName(const String& name) {
	this->name = name;
}
void Piece::setColour( bool colour) {
	this->colour = colour;
}
const String& Piece::getName() const {
	return name;
}
bool Piece::getColour() const {
	return colour;
}