#pragma once
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

	Color GetColor() {
		return color;
	}
};

