#pragma once
#include "String.h"
class Piece
{
	public:
		Piece();
		Piece(const String& name, bool color);
		const String& getName() const;
		bool getColour() const;
		void setName(const String& name);
		void setColour(bool colour);

	private:
	String name;
	bool colour; // 1 - white, 2 - black	

};

