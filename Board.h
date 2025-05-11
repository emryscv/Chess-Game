#pragma once
#include "Pieces/Piece.h";

class Board
{
	Piece* board[8][8];
	Color turn;

public:
	Board();
	bool isValidMove(int originX, int originY, int destinationX, int destinantionY);
	void Move(int originX, int originY, int destinationX, int destinantionY);
	void SwitchTurn();
	void PrintBoard();
};

