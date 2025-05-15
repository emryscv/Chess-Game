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
	int x;
	int y;

public:
	Piece(const Color& color, const int& x, const int& y) {
		this->color = color;
		this->x = x;
		this->y = y;
	}
	
	void SetCoordinates(const int& x, const int& y) {
		this->x = x;
		this->y = y;
	}

	Color GetColor()  const {
		return color;
	}

	virtual std::string GetRepresentation() const = 0;

	virtual bool IsValidMove(const int& destinationX, const int& destinationY) const = 0;
};

