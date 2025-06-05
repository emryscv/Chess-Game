#include "Board.h"
#include "iostream"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"


class Game {
	Board board;
public:
	bool IsValidPiece(int y, int X) const; //TODO fix this
	bool IsAValidMove(int originY, int originX, int destinationY, int destinationX);
	void Move(int originY, int originX, int destinationY, int destinationX);

	Piece* const (&GetBoard() const)[8][8]{
		return board.GetBoard();
	}
};