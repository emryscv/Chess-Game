#include "Knight.h"

std::string Knight::GetRepresentation() const {
	return "Kn";
}

bool Knight::IsValidMove(const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(x - 2 == destinationX and (y + 1 == destinationY or y - 1 == destinationY) or
			y - 2 == destinationY and (x + 1 == destinationX or x - 1 == destinationX) or
			x + 2 == destinationX and (y + 1 == destinationY or y - 1 == destinationY) or
			y + 2 == destinationY and (x + 1 == destinationX or x - 1 == destinationX));
}