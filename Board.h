#pragma once
#include "Pieces/Piece.h";
#include "Pieces/King.h";
#include <vector>
class Board
{
	Piece* board[8][8];
	Color turn;
	bool isCheck;
	bool promotePawn;
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
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
	bool IsCheck(const Color& color, const int& originX, const int& originY, const int& destinationX, const int& destinationY);
	bool IsUnderThreat(const Color& color, const int& positionX, const int& positionY) const;
	bool isCheckMate();

	void SetPosition(const int& x, const int& y, const int& option);

	static bool ValidCoordinates(const int& x, const int& y);

	const Piece* GetPosition(const int& x, const int& y) const {
		return board[x][y];
	}

	const Color& GetTurn() const {
		return turn;
	}
	const bool& GetIsCheck() const{
		return isCheck;
	}
	const bool& GetPromotePawn() const {
		return promotePawn;
	}

	void SetCheck(const bool& isCheck) {
		this->isCheck = isCheck;
	}
	void ResetChangePiece() {
		promotePawn = false;
	}
};