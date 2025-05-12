#include "Bishop.h"

std::string Bishop::GetRepresentation() const {
	return "Bi";
}

bool Bishop::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const
{
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(originX - originY == destinationX - destinationY or originX - destinationX == destinationY - originY);
}
