#include "Bishop.h"

std::string Bishop::GetRepresentation() const {
	return "Bi";
}

bool Bishop::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const
{
	return (x - y == destinationX - destinationY or x - destinationX == destinationY - y);
}

std::vector<std::pair<int, int>> Bishop::GetAllPossibleMoves() const
{
	std::vector<std::pair<int, int>> posibleMoves;

	for (int i = 0; x + i < 8 or y + i < 8; i++) {
		posibleMoves.push_back(std::make_pair(x + i, y + i));
	}
	for (int i = 0; x + i >= 0 or y + i >= 0; i--) {
		posibleMoves.push_back(std::make_pair(x + i, y + i));
	}
	for (int i = 0; x + i < 8 or y - i >= 0; i++) {
		posibleMoves.push_back(std::make_pair(x + i, y - i));
	}
	for (int i = 0; x - i >= 0 or y + i < 8; i++) {
		posibleMoves.push_back(std::make_pair(x - i, y + i));
	}

	return posibleMoves;
}
