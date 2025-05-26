#include "Knight.h"

std::string Knight::GetRepresentation() const {
	return "Kn";
}

bool Knight::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const {
	return (x - 2 == destinationX and (y + 1 == destinationY or y - 1 == destinationY) or
		    y - 2 == destinationY and (x + 1 == destinationX or x - 1 == destinationX) or
		    x + 2 == destinationX and (y + 1 == destinationY or y - 1 == destinationY) or
		    y + 2 == destinationY and (x + 1 == destinationX or x - 1 == destinationX));
}