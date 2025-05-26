#include "Queen.h"

std::string Queen::GetRepresentation() const{
	return "Qu";
}

bool Queen::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const {
	return (x == destinationX or y == destinationY or x - y == destinationX - destinationY or x - destinationX == destinationY - y);
}