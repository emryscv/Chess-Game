#pragma once
#include "Pieces/Piece.h";
#include "Pieces/King.h";
#include <vector>
class Board
{
	Piece* board[8][8];
	std::vector<Piece*> whitePieces;
	std::vector<Piece*> blackPieces;
	bool promotePawn;
	bool leftRookNotMoved[2] = { true, true };
	bool rightRookNotMoved[2] = { true, true };
	bool kingNotMoved[2] = {true, true};

	static void MinMax(const int& a, const int& b, int& min, int& max);
	bool CheckCondtion(int x, int y, const int& dx, const int& dy, const std::string& firstRep, const std::string& secondRep, const Color& color) const;
	
public:
	Board();
	bool IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY, Color turn);
	bool Move(const int& originX, const int& originY, const int& destinationX, const int& destinationY, Color turn);
	void PrintBoard() const;
	bool IsCheck(const Color& color) const;
	bool IsCheck(const Color& color, const int& originX, const int& originY, const int& destinationX, const int& destinationY);
	bool IsUnderThreat(const Color& color, const int& positionX, const int& positionY) const;
	bool IsCheckMate(Color turn);

	void SetPosition(const int& x, const int& y, const int& option, Color color);

	static bool ValidCoordinates(const int& x, const int& y);

	Piece* const (&GetBoard() const)[8][8]{
		return board;
	}

	const Piece* GetPosition(const int& x, const int& y) const {
		return board[x][y];
	}

	const bool& GetPromotePawn() const {
		return promotePawn;
	}

	void ResetPromotePawn() {
		promotePawn = false;
	}
};