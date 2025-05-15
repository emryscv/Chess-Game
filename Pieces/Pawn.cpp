#include "Pawn.h"

std::string Pawn::GetRepresentation() const {
	return "Pa";
}

bool Pawn::IsValidMove(const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		y == destinationY and
		((color == Color::White and (x - 1 == destinationX or (x == 6 and destinationX == 4))) or
		(color == Color::Black and (x + 1 == destinationX or (x == 1 and destinationX == 3))))
		;
}