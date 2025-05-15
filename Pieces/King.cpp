#include "King.h"

std::string King::GetRepresentation() const {
	return "Ki";
}

std::pair<int, int> King::GetCoordinates() const
{
	return std::pair<int, int>(x, y);
}

bool King::IsValidMove(const int& destinationX, const int& destinationY) const
{
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(x - 1 == destinationX and (y - 1 == destinationY or y == destinationY or y + 1 == destinationY) or
		x == destinationX and (y - 1 == destinationY or y + 1 == destinationY) or
		x + 1 == destinationX and (y - 1 == destinationY or y == destinationY or y + 1 == destinationY));
}
