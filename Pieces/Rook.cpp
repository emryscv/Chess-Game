#include "Rook.h";

std::string Rook::GetRepresentation() const {
	return "Ro";
}

bool Rook::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and
		(originX == destinationX or originY == destinationY);
}