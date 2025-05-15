#include "Board.h"
#include "Pieces/King.h"
#include "Pieces/Queen.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Pawn.h"
#include <iostream>

Board::Board() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = nullptr;
		}
	}

	board[0][0] = new Rook(Color::Black, 0, 0);
	board[0][1] = new Knight(Color::Black, 0, 1);
	board[0][2] = new Bishop(Color::Black, 0, 2);
	board[0][3] = new Queen(Color::Black, 0, 3);
	board[0][4] = blackKing = new King(Color::Black, 0, 4);
	board[0][5] = new Bishop(Color::Black, 0, 5);
	board[0][6] = new Knight(Color::Black, 0, 6);
	board[0][7] = new Rook(Color::Black, 0, 7);

	board[1][0] = new Pawn(Color::Black, 1, 0);
	board[1][1] = new Pawn(Color::Black, 1, 1);
	board[1][2] = new Pawn(Color::Black, 1, 2);
	board[1][3] = new Pawn(Color::Black, 1, 3);
	board[1][4] = new Pawn(Color::Black, 1, 4);
	board[1][5] = new Pawn(Color::Black, 1, 5);
	board[1][6] = new Pawn(Color::Black, 1, 6);
	board[1][7] = new Pawn(Color::Black, 1, 7);

	board[6][0] = new Pawn(Color::White, 6, 0);
	board[6][1] = new Pawn(Color::White, 6, 1);
	board[6][2] = new Pawn(Color::White, 6, 2);
	board[6][3] = new Pawn(Color::White, 6, 3);
	board[6][4] = new Pawn(Color::White, 6, 4);
	board[6][5] = new Pawn(Color::White, 6, 5);
	board[6][6] = new Pawn(Color::White, 6, 6);
	board[6][7] = new Pawn(Color::White, 6, 7);

	board[7][0] = new Rook(Color::White, 7, 0);
	board[7][1] = new Knight(Color::White, 7, 1);
	board[7][2] = new Bishop(Color::White, 7, 2);
	board[7][3] = new Queen(Color::White, 7, 3);
	board[7][4] = whiteKing = new King(Color::White, 7, 4);
	board[7][5] = new Bishop(Color::White, 7, 5);
	board[7][6] = new Knight(Color::White, 7, 6);
	board[7][7] = new Rook(Color::White, 7, 7);

	turn = Color::White;
}

bool Board::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY)
{
	//add some logic to check "check"

	std::cout << board[originX][originY]->IsValidMove(destinationX, destinationY) << "\n";
	std::cout << (board[destinationX][destinationY] == nullptr) << "\n";
	if (board[destinationX][destinationY] != nullptr) std::cout << (board[destinationX][destinationY]->GetColor() != turn) << "\n";

	if (board[originX][originY]->IsValidMove(destinationX, destinationY) and (board[destinationX][destinationY] == nullptr or board[destinationX][destinationY]->GetColor() != turn)) {
		int min;
		int max;
		if (originX == destinationX) {
			MinMax(originY, destinationY, min, max);
			for (int i = min + 1; i < max; i++) {
				if (board[originX][i] != nullptr) return false;
			}
		}
		else if (originY == destinationY) {
			MinMax(originX, destinationX, min, max);
			for (int i = min + 1; i < max; i++) {
				if (board[i][originY] != nullptr) return false;
			}
		}
		else if (originX - originY == destinationX - destinationY) {
			if (originX < destinationX) {
				min = originX;
				max = destinationX;
				for (int i = 1; i < max - min; i++) {
					if (board[originX + i][originY + i] != nullptr) return false;
				}
			}
			else {
				min = destinationX;
				max = originX;
				for (int i = 1; i < max - min; i++) {
					if (board[originX - i][originY - i] != nullptr) return false;
				}
			}
		}
		else if (originX - destinationX == destinationY - originY) {
			if (originX < destinationX) {
				min = originX;
				max = destinationX;
				for (int i = 1; i < max - min; i++) {
					if (board[originX + i][originY - i] != nullptr) return false;
				}
			}
			else {
				min = destinationX;
				max = originX;
				for (int i = 1; i < max - min; i++) {
					if (board[originX - i][originY + i] != nullptr) return false;
				}
			}
		}

		//Move the piece virtualy to check for check.
		Move(originX, originY, destinationX, destinationY);
		
		if (IsCheck(turn)) {
			Move(destinationX, destinationY, originX, originY);
			return false;
		}
		else {
			Move(destinationX, destinationY, originX, originY);
			return true;
		}
	}
	return false;
}

void Board::Move(const int& originX, const int& originY, const int& destinationX, const int& destinationY)
{
	//add some logic to know the piece is no longer in board
	if(board[destinationX][destinationY] != nullptr) delete board[destinationX][destinationY];

	board[destinationX][destinationY] = board[originX][originY];
	board[destinationX][destinationY]->SetCoordinates(destinationX, destinationY);
	board[originX][originY] = nullptr;

}

void Board::SwitchTurn()
{
	turn = (turn == Color::White) ? Color::Black : Color::White;
}

void Board::PrintBoard() const
{
	bool isBlack = false;

	for (int i = 0; i < 8; i++) {
		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 6; l++) {
				if (isBlack) std::cout << 'x';
				else std::cout << ' ';
			}
			isBlack = !isBlack;
		}
		std::cout << "\n";
		for (int k = 0; k < 8; k++) {
			if (isBlack) std::cout << 'x';
			else std::cout << ' ';

			std::cout << " ";
			if (board[i][k] != nullptr) {
				std::cout << board[i][k]->GetRepresentation();
			}
			else {
				std::cout << "  ";
			}

			std::cout << " ";

			if (isBlack) std::cout << 'x';
			else std::cout << ' ';

			isBlack = !isBlack;
		}
		std::cout << "\n";
		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 6; l++) {
				if (isBlack) std::cout << 'x';
				else std::cout << ' ';
			}
			isBlack = !isBlack;
		}
		std::cout << "\n";

		isBlack = !isBlack;
	}
}

bool Board::IsCheck(const Color& color) const
{
	King* king = color == Color::White ? whiteKing : blackKing;
	std::pair<int, int> coordinates = king->GetCoordinates();

	int dxKnight[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int dyKnight[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };

	int dxKing[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
	int dyKing[8] = {0, -1, -1, -1, 0, 1, 1, 1};

	//Check pawns
	//TODO It is only white check tho.

	int x = color == Color::White ? coordinates.first - 1 : coordinates.first + 1;
	int y = coordinates.second + 1;

	if (ValidCoordinates(x, y) and board[x][y] != nullptr and board[x][y]->GetColor() != color and board[x][y]->GetRepresentation() == "Pa") return true;

	y = coordinates.second - 1;

	if (ValidCoordinates(x, y) and board[x][y] != nullptr and board[x][y]->GetColor() != color and board[x][y]->GetRepresentation() == "Pa") return true;

	//Check Knights
	for (int i = 0; i < 8; i++) {
		x = coordinates.first + dxKnight[i];
		y = coordinates.second + dyKnight[i];
		if (ValidCoordinates(x, y) and
			board[x][y] != nullptr and
			board[x][y]->GetColor() != color and
			board[x][y]->GetRepresentation() == "Kn") {
			return true;
		}
	}

	//Check for other King
	for (int i = 0; i < 8; i++) {
		x = coordinates.first + dxKing[i];
		y = coordinates.second + dyKing[i];
		if (ValidCoordinates(x, y) and
			board[x][y] != nullptr and
			board[x][y]->GetColor() != color and
			board[x][y]->GetRepresentation() == "Ki") {
			return true;
		}
	}

	//Check Rook, Queen and Bishop
	return (CheckCondtion(coordinates.first, coordinates.second, 1, 0, "Ro", "Qu", color) or
		CheckCondtion(coordinates.first, coordinates.second, 0, 1, "Ro", "Qu", color) or
		CheckCondtion(coordinates.first, coordinates.second, -1, 0, "Ro", "Qu", color) or
		CheckCondtion(coordinates.first, coordinates.second, 0, -1, "Ro", "Qu", color) or
		CheckCondtion(coordinates.first, coordinates.second, 1, 1, "Bi", "Qu", color) or
		CheckCondtion(coordinates.first, coordinates.second, -1, -1, "Bi", "Qu", color) or
		CheckCondtion(coordinates.first, coordinates.second, 1, -1, "Bi", "Qu", color) or
		CheckCondtion(coordinates.first, coordinates.second, -1, 1, "Bi", "Qu", color));
}

void Board::MinMax(const int& a, const int& b, int& min, int& max) {
	if (a > b) {
		min = b;
		max = a;
	}
	else {
		min = a;
		max = b;
	}
}

bool Board::CheckCondtion(int x, int y, const int& dx, const int& dy, const std::string& firstRep, const std::string& secondRep, const Color& color) const {
	x += dx;
	y += dy;

	while (x >= 0 && x < 8 && y >= 0 && y < 8) {
		if (board[x][y] != nullptr) {
			if (board[x][y]->GetColor() == color) {
				break;
			}
			else {
				std::string rep = board[x][y]->GetRepresentation();
				if (rep == firstRep || rep == secondRep) {
					return true;
				}
				break;
			}
		}
		x += dx;
		y += dy;
	}
	return false;
}

bool Board::ValidCoordinates(const int& x, const int& y)
{
	return 0 <= x && x < 8 && 0 <= y && y < 8;
}


