#include "King.h"

std::string King::GetRepresentation() const {
	return "Ki";
}

std::pair<int, int> King::GetCoordinates() const
{
	return std::make_pair(x, y);
}

bool King::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const
{
	return (x - 1 == destinationX and (y - 1 == destinationY or y == destinationY or y + 1 == destinationY) or
			x == destinationX and (y - 1 == destinationY or y + 1 == destinationY) or
			x + 1 == destinationX and (y - 1 == destinationY or y == destinationY or y + 1 == destinationY)) or
		
			(context.kingNotMoved and (destinationX == 7 or destinationX == 0) and
			((destinationY == 6 and context.rightRookNotMoved) or
			 (destinationY == 2 and context.leftRookNotMoved)));
}
