#include "Queen.h"

std::string Queen::GetRepresentation() const{
	return "Qu";
}

bool Queen::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(originX == destinationX or originY == destinationY or originX - originY == destinationX - destinationY or originX - destinationX == destinationY - originY);
}