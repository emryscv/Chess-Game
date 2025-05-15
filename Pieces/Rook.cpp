#include "Rook.h";

std::string Rook::GetRepresentation() const {
	return "Ro";
}

bool Rook::IsValidMove(const int& destinationX, const int& destinationY) const {
	return 0 <= destinationX and destinationX <= 7 and 0 <= destinationY and destinationY <= 7 and (x == destinationX or y == destinationY);
}