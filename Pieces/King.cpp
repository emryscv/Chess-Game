#include "King.h"

std::string King::GetRepresentation() const {
	return "Ki";
}

bool King::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const
{
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(originX - 1 == destinationX and (originY - 1 == destinationY or originY == destinationY or originY + 1 == destinationY) or
		originX == destinationX and (originY - 1 == destinationY or originY + 1 == destinationY) or
		originX + 1 == destinationX and (originY - 1 == destinationY or originY == destinationY or originY + 1 == destinationY));
}
