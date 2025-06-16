#include "Pawn.h"

std::string Pawn::GetRepresentation() const {
	return "Pa";
}

bool Pawn::IsValidMove(const int& destinationX, const int& destinationY, const MoveContext& context) const {
	return (
			(
				color == Color::White and (
					(
						x - 1 == destinationX and (
							(y == destinationY and !context.positionOccupied) or ((y == destinationY - 1 or y == destinationY + 1) and context.positionOccupied)
						)
					) or (
						x == 6 and destinationX == 4 and y == destinationY and !context.positionOccupied
					)
				)
			) or (
				color == Color::Black and (
					(
						x + 1 == destinationX and (
							(y == destinationY and !context.positionOccupied) or ((y == destinationY - 1 or y == destinationY + 1) and context.positionOccupied)
						)
					) or (
						x == 1 and destinationX == 3 and y == destinationY and !context.positionOccupied
					)
				)
			)
		);
}

std::vector<std::pair<int, int>> Pawn::GetAllPossibleMoves() const
{
	std::vector<std::pair<int, int>> posibleMoves;

	if (color == Color::White) {
		posibleMoves.push_back(std::make_pair(x + 1, y));
		posibleMoves.push_back(std::make_pair(x + 1, y + 1));
		posibleMoves.push_back(std::make_pair(x + 1, y - 1));
		if(x == 6) posibleMoves.push_back(std::make_pair(x + 2, y));
	}
	else {
		posibleMoves.push_back(std::make_pair(x - 1, y));
		posibleMoves.push_back(std::make_pair(x - 1, y + 1));
		posibleMoves.push_back(std::make_pair(x - 1, y - 1));
		if (x == 1) posibleMoves.push_back(std::make_pair(x - 2, y));
	}

	return posibleMoves;
}
