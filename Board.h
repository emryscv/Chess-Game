#pragma once
#include "Pieces/Piece.h";
#include "Pieces/King.h";

class Board
{
	Piece* board[8][8];
	Color turn;
	bool isCheck;
	King* whiteKing;
	King* blackKing;
	bool leftRookNotMoved[2] = { true, true };
	bool rightRookNotMoved[2] = { true, true };
	bool kingNotMoved[2] = {true, true};

	static void MinMax(const int& a, const int& b, int& min, int& max);
	bool CheckCondtion(int x, int y, const int& dx, const int& dy, const std::string& firstRep, const std::string& secondRep, const Color& color) const;
	
public:
	Board();
	bool IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY);
	void Move(const int& originX, const int& originY, const int& destinationX, const int& destinationY);
	void SwitchTurn();
	void PrintBoard() const;
	bool IsCheck(const Color& color) const;
	
	static bool ValidCoordinates(const int& x, const int& y);

	const Color GetTurn() const {
		return turn;
	}
	const Piece* GetPosition(const int& x, const int& y) const{
		return board[x][y];
	}
	const bool GetIsCheck() const{
		return isCheck;
	}

	void SetCheck(const bool& isCheck) {
		this->isCheck = isCheck;
	}

};

