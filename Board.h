#pragma once
#include "Pieces/Piece.h";
#include "Pieces/King.h";

class Board
{
	Piece* board[8][8];
	Color turn;
	King* whiteKing;
	King* blackKing;

	static void MinMax(const int& a, const int& b, int& min, int& max);
	static bool ValidCoordinates(const int& x, const int& y);
	bool CheckCondtion(int x, int y, const int& dx, const int& dy, const std::string& firstRep, const std::string& secondRep, const Color& color) const;
	
public:
	Board();
	bool IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY);
	void Move(const int& originX, const int& originY, const int& destinationX, const int& destinationY);
	void SwitchTurn();
	void PrintBoard() const;
	bool IsCheck(const Color& color) const;

	const Color GetTurn() const {
		return turn;
	}
	const Piece* GetPosition(const int& x, const int& y) {
		return board[x][y];
	}
};

