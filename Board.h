#pragma once
#include "Pieces/Piece.h";

class Board
{
	Piece* board[8][8];
	Color turn;

public:
	Board();
	bool IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinantionY);
	void Move(const int& originX, const int& originY, const int& destinationX, const int& destinantionY);
	void SwitchTurn();
	void PrintBoard() const;

	const Color GetTurn() const {
		return turn;
	}
	const Piece* GetPosition(const int& x, const int& y) {
		return board[x][y];
	}
};

