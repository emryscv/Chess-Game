#pragma once
#include "iostream";
#include "string";

enum Color {
	Black,
	White
};

class Piece
{
	Color color;

public:
	Piece(Color color) {
		this->color = color;
	}
	
	Color GetColor()  const {
		return color;
	}

	virtual std::string GetRepresentation() const = 0;

	virtual bool IsValidMove(int originX, int originY, int destinationX, int destinantionY) const = 0;
};

