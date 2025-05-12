#include "Pawn.h"

std::string Pawn::GetRepresentation() const {
	return "Pa";
}

bool Pawn::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		originY == destinationY and
		((color == Color::White and (originX - 1 == destinationX or (originX == 6 and destinationX == 4))) or
		(color == Color::Black and (originX + 1 == destinationX or (originX == 1 and destinationX == 3))))
		;
}