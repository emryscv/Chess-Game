#include "Rook.h";

std::string Rook::GetRepresentation() const {
	return "Ro";
}

bool Rook::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const {
	return (x == destinationX or y == destinationY);
}