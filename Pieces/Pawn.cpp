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