#include "Knight.h"

std::string Knight::GetRepresentation() const {
	return "Kn";
}

bool Knight::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(originX - 2 == destinationX and (originY + 1 == destinationY or originY - 1 == destinationY) or
			originY - 2 == destinationY and (originX + 1 == destinationX or originX - 1 == destinationX) or
			originX + 2 == destinationX and (originY + 1 == destinationY or originY - 1 == destinationY) or
			originY + 2 == destinationY and (originX + 1 == destinationX or originX - 1 == destinationX));
}