#include "Board.h"
#include "iostream"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"


class Game {
	Board board;
	Color turn;
	bool isCheck;
	bool isCheckMate;

public:
	Game(): turn(Color::White), isCheck(false), isCheckMate(false) {}
	bool IsValidPiece(int y, int X) const; //TODO fix this coordinates
	bool IsAValidMove(int originY, int originX, int destinationY, int destinationX);
	void Move(int originY, int originX, int destinationY, int destinationX);
	void SwitchTurn();
	void AfterMove();
	void PromotePawn(int destinationX, int destinationY, int option);

	Piece* const (&GetBoard() const)[8][8]{
		return board.GetBoard();
	}

	const Color& GetTurn() const {
		return turn;
	}

	const bool& GetIsCheck() const {
		return isCheck;
	}

	const bool& GetIsCheckMAte() const {
		return isCheckMate;
	}

	bool GetPromotePawn() const {
		return board.GetPromotePawn();
	}

	void SetCheck(const bool& isCheck) {
		this->isCheck = isCheck;
	}
};