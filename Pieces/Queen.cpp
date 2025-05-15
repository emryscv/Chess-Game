#include "Queen.h"

std::string Queen::GetRepresentation() const{
	return "Qu";
}

bool Queen::IsValidMove(const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(x == destinationX or y == destinationY or x - y == destinationX - destinationY or x - destinationX == destinationY - y);
}