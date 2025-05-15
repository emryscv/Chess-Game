#include "Bishop.h"

std::string Bishop::GetRepresentation() const {
	return "Bi";
}

bool Bishop::IsValidMove(const int& destinationX, const int& destinationY) const
{
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(x - y == destinationX - destinationY or x - destinationX == destinationY - y);
}
