#pragma once
#include "iostream";
#include "string";

enum Color {
	Black,
	White
};

class Piece
{
protected:
	Color color;

public:
	Piece(const Color& color) {
		this->color = color;
	}
	
	Color GetColor()  const {
		return color;
	}

	virtual std::string GetRepresentation() const = 0;

	virtual bool IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const = 0;
};

