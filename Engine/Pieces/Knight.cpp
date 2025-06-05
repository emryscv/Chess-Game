#include "Knight.h"

std::string Knight::GetRepresentation() const {
	return "Kn";
}

bool Knight::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const {
	return (x - 2 == destinationX and (y + 1 == destinationY or y - 1 == destinationY) or
		    y - 2 == destinationY and (x + 1 == destinationX or x - 1 == destinationX) or
		    x + 2 == destinationX and (y + 1 == destinationY or y - 1 == destinationY) or
		    y + 2 == destinationY and (x + 1 == destinationX or x - 1 == destinationX));
}

std::vector<std::pair<int, int>> Knight::GetAllPosibleMoves() const
{
	int dxKnight[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int dyKnight[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };
	std::vector<std::pair<int, int>> posibleMoves;

	for (int i = 0; i < 8; i++) {
		posibleMoves.push_back(std::make_pair(x + dxKnight[i], y + dyKnight[i]));
	}

	return posibleMoves;
}
