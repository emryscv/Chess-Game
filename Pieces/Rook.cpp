#include "Rook.h";

std::string Rook::GetRepresentation() const {
	return "Ro";
}

bool Rook::IsValidMove(int originX, int originY, int destinationX, int destinationY) const {
	return true;
}