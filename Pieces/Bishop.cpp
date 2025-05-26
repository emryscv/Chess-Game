#include "Bishop.h"

std::string Bishop::GetRepresentation() const {
	return "Bi";
}

bool Bishop::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const
{
	return (x - y == destinationX - destinationY or x - destinationX == destinationY - y);
}
