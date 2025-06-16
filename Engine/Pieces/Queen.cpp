#include "Queen.h"

std::string Queen::GetRepresentation() const{
	return "Qu";
}

bool Queen::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const {
	return (x == destinationX or y == destinationY or x - y == destinationX - destinationY or x - destinationX == destinationY - y);
}

std::vector<std::pair<int, int>> Queen::GetAllPossibleMoves() const
{
	std::vector<std::pair<int, int>> posibleMoves;

	for (int i = x; i >= 0; i--) {
		posibleMoves.push_back(std::make_pair(i, y));
	}
	for (int i = x; i < 8; i++) {
		posibleMoves.push_back(std::make_pair(i, y));
	}
	for (int j = y; j >= 0; j--) {
		posibleMoves.push_back(std::make_pair(x, j));
	}
	for (int j = y; j < 8; j++) {
		posibleMoves.push_back(std::make_pair(x, j));
	}
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
