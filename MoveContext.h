#pragma once
struct MoveContext {
	bool kingNotMoved;
	bool rightRookNotMoved;
	bool leftRookNotMoved;
	bool positionOccupied;

	MoveContext(bool kingNotMoved, bool rightRookNotMoved, bool leftRookNotMoved, bool positionOccupied) : kingNotMoved(kingNotMoved), rightRookNotMoved(rightRookNotMoved), leftRookNotMoved(leftRookNotMoved), positionOccupied(positionOccupied) {};
};