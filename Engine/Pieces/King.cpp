#include "King.h"

std::string King::GetRepresentation() const {
	return "Ki";
}

bool King::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const
{
	return (x - 1 == destinationX and (y - 1 == destinationY or y == destinationY or y + 1 == destinationY) or
			x == destinationX and (y - 1 == destinationY or y + 1 == destinationY) or
			x + 1 == destinationX and (y - 1 == destinationY or y == destinationY or y + 1 == destinationY)) or
		
			(context.kingNotMoved and (destinationX == 7 or destinationX == 0) and
			((destinationY == 6 and context.rightRookNotMoved) or
			 (destinationY == 2 and context.leftRookNotMoved)));
}

std::vector<std::pair<int, int>> King::GetAllPossibleMoves() const
{
	int dxKing[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int dyKing[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };
	std::vector<std::pair<int, int>> possibleMoves;

	for (int i = 0; i < 8; i++) {
		possibleMoves.push_back(std::make_pair(x + dxKing[i], y + dyKing[i]));
	}

	return possibleMoves;
	// TODO: insert return statement here
}
