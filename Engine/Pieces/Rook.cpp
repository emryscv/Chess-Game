#include "Rook.h";

std::string Rook::GetRepresentation() const {
	return "Ro";
}

bool Rook::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const {
	return (x == destinationX or y == destinationY);
}

std::vector<std::pair<int, int>> Rook::GetAllPossibleMoves() const
{
	std::vector<std::pair<int, int>> posibleMoves;

	for (int i = x - 1; i >= 0; i--) {
		posibleMoves.push_back(std::make_pair(i, y));
	}
	for (int i = x + 1; i < 8; i++) {
		posibleMoves.push_back(std::make_pair(i, y));
	}
	for (int j = y - 1; j >= 0; j--) {
		posibleMoves.push_back(std::make_pair(x, j));
	}
	for (int j = y + 1; j < 8; j++) {
		posibleMoves.push_back(std::make_pair(x, j));
	}

	return posibleMoves;
}
