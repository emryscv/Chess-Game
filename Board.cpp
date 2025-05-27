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
	board[0][4] = new King(Color::Black, 0, 4);
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
	board[5][5] = new Queen(Color::White, 5, 5);
	board[7][4] = new King(Color::White, 7, 4);
	board[7][5] = new Bishop(Color::White, 7, 5);
	board[7][6] = new Knight(Color::White, 7, 6);
	board[7][7] = new Rook(Color::White, 7, 7);

	blackPieces.push_back(board[0][4]);
	blackPieces.push_back(board[0][0]);
	blackPieces.push_back(board[0][1]);
	blackPieces.push_back(board[0][2]);
	blackPieces.push_back(board[0][3]);
	blackPieces.push_back(board[0][5]);
	blackPieces.push_back(board[0][6]);
	blackPieces.push_back(board[0][7]);

	blackPieces.push_back(board[1][0]);
	blackPieces.push_back(board[1][1]);
	blackPieces.push_back(board[1][2]);
	blackPieces.push_back(board[1][3]);
	blackPieces.push_back(board[1][4]);
	blackPieces.push_back(board[1][5]);
	blackPieces.push_back(board[1][6]);
	blackPieces.push_back(board[1][7]);

		
	whitePieces.push_back(board[7][4]);
	whitePieces.push_back(board[7][0]);
	whitePieces.push_back(board[7][1]);
	whitePieces.push_back(board[7][2]);
	whitePieces.push_back(board[5][5]);
	whitePieces.push_back(board[7][5]);
	whitePieces.push_back(board[7][6]);
	whitePieces.push_back(board[7][7]);
	
	whitePieces.push_back(board[6][0]);
	whitePieces.push_back(board[6][1]);
	whitePieces.push_back(board[6][2]);
	whitePieces.push_back(board[6][3]);
	whitePieces.push_back(board[6][4]);
	whitePieces.push_back(board[6][5]);
	whitePieces.push_back(board[6][6]);
	whitePieces.push_back(board[6][7]);

	turn = Color::White;
}

bool Board::IsValidMove(const int& originX, const int& originY, const int& destinationX, const int& destinationY)
{
	//check for x and y in board
	if (!ValidCoordinates(destinationX, destinationY)) return false;

	//check if the destination is empty or enemy position
	if ((board[destinationX][destinationY] != nullptr and (board[destinationX][destinationY]->GetColor() == turn or board[destinationX][destinationY]->GetRepresentation() == "Ki"))) return false;

	//create a context
	MoveContext context(kingNotMoved[turn], rightRookNotMoved[turn], leftRookNotMoved[turn], board[destinationX][destinationY] != nullptr);

	//check if the move make sense according the rules
	if (board[originX][originY]->IsValidMove(destinationX, destinationY, context)) {
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

		if (board[originX][originY]->GetRepresentation() == "Ki" and originY == 4 and (originX == 0 or originX == 7) and originX == destinationX) {
			if (destinationY == 6 and IsUnderThreat(turn, originX, 5)) return false;
			if (destinationY == 2 and IsUnderThreat(turn, originX, 3)) return false;
		}

		//Move the piece virtualy to check for check.
		return !IsCheck(turn, originX, originY, destinationX, destinationY);
	}

	return false;
}

void Board::Move(const int& originX, const int& originY, const int& destinationX, const int& destinationY)
{
	//add some logic to know the piece is no longer in board
	if (board[destinationX][destinationY] != nullptr) {
		std::vector<Piece*>& pieces = turn == Color::White ? blackPieces : whitePieces;
		
		for (int i = 0; i < pieces.size(); i++) {
			if (pieces[i]->GetCoordinates().first == destinationX and pieces[i]->GetCoordinates().second == destinationY) {
				pieces.erase(pieces.begin() + i);
				break;
			}
		}

		delete board[destinationX][destinationY];
	}
	board[destinationX][destinationY] = board[originX][originY];
	board[destinationX][destinationY]->SetCoordinates(destinationX, destinationY);
	board[originX][originY] = nullptr;

	std::string representation = board[destinationX][destinationY]->GetRepresentation();

	if (board[destinationX][destinationY]->GetRepresentation() == "Ki" and kingNotMoved[turn] and (destinationX == 7 or destinationX == 0)) {
		if (destinationY == 6 and rightRookNotMoved[turn]) {
			Move(destinationX, 7, destinationX, 5);
		}
		else if (destinationY == 2 and leftRookNotMoved[turn]) {
			Move(destinationX, 0, destinationX, 3);
		}
	}

	if (representation == "Ki" and kingNotMoved[turn]) {
		kingNotMoved[turn] = false;
	}
	else if (representation == "Ro" and originX == 7) {
		if (originY == 0 and leftRookNotMoved[turn]) {
			leftRookNotMoved[turn] = false;
		}
		else if (originY == 7 and rightRookNotMoved[turn]) {
			rightRookNotMoved[turn] = false;
		}
	}
	else if (representation == "Pa" and (destinationX == 0 or destinationX == 7)) {
		promotePawn = true;
	}
}

void Board::SwitchTurn()
{
	turn = (turn == Color::White) ? Color::Black : Color::White;
	std::cout << "\nWhite: ";
	for (int i = 0; i < whitePieces.size(); i++) {
		std::cout << whitePieces[i]->GetRepresentation() << " ";
	}
	std::cout << "\nBlack: ";
	for (int i = 0; i < blackPieces.size(); i++) {
		std::cout << blackPieces[i]->GetRepresentation() << " ";
	}
	int option;
	std::cin >> option;
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
	Piece* king = color == Color::White ? whitePieces[0] : blackPieces[0]; //It's king
	std::pair<int, int> coordinates = king->GetCoordinates();

	return IsUnderThreat(color, coordinates.first, coordinates.second);
}


bool Board::IsCheck(const Color& color, const int& originX, const int& originY, const int& destinationX, const int& destinationY) {

	Piece* aux = board[destinationX][destinationY];
	board[destinationX][destinationY] = board[originX][originY];
	board[destinationX][destinationY]->SetCoordinates(destinationX, destinationY);
	board[originX][originY] = nullptr;

	bool answer = IsCheck(color);

	board[originX][originY] = board[destinationX][destinationY];
	board[originX][originY]->SetCoordinates(originX, originY);
	board[destinationX][destinationY] = aux;

	return answer;
}

bool Board::IsUnderThreat(const Color& color, const int& positionX, const int& positionY) const {
	int dxKnight[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
	int dyKnight[8] = { -1, -2, -2, -1, 1, 2, 2, 1 };

	int dxKing[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
	int dyKing[8] = { 0, -1, -1, -1, 0, 1, 1, 1 };

	//Check pawns
	//TODO It is only white check tho.

	int x = color == Color::White ? positionX - 1 : positionX + 1;
	int y = positionY + 1;

	if (ValidCoordinates(x, y) and board[x][y] != nullptr and board[x][y]->GetColor() != color and board[x][y]->GetRepresentation() == "Pa") return true;

	y = positionY - 1;

	if (ValidCoordinates(x, y) and board[x][y] != nullptr and board[x][y]->GetColor() != color and board[x][y]->GetRepresentation() == "Pa") return true;

	//Check Knights
	for (int i = 0; i < 8; i++) {
		x = positionX + dxKnight[i];
		y = positionY + dyKnight[i];
		if (ValidCoordinates(x, y) and
			board[x][y] != nullptr and
			board[x][y]->GetColor() != color and
			board[x][y]->GetRepresentation() == "Kn") {
			return true;
		}
	}

	//Check for other King
	for (int i = 0; i < 8; i++) {
		x = positionX + dxKing[i];
		y = positionY + dyKing[i];
		if (ValidCoordinates(x, y) and
			board[x][y] != nullptr and
			board[x][y]->GetColor() != color and
			board[x][y]->GetRepresentation() == "Ki") {
			return true;
		}
	}

	//Check Rook, Queen and Bishop
	return (CheckCondtion(positionX, positionY, 1, 0, "Ro", "Qu", color) or
		CheckCondtion(positionX, positionY, 0, 1, "Ro", "Qu", color) or
		CheckCondtion(positionX, positionY, -1, 0, "Ro", "Qu", color) or
		CheckCondtion(positionX, positionY, 0, -1, "Ro", "Qu", color) or
		CheckCondtion(positionX, positionY, 1, 1, "Bi", "Qu", color) or
		CheckCondtion(positionX, positionY, -1, -1, "Bi", "Qu", color) or
		CheckCondtion(positionX, positionY, 1, -1, "Bi", "Qu", color) or
		CheckCondtion(positionX, positionY, -1, 1, "Bi", "Qu", color));
}

bool Board::isCheckMate()
{
	std::vector<Piece*>& pieces = turn == Color::White ? whitePieces : blackPieces;

	for (Piece* piece : pieces) {
		std::vector<std::pair<int, int>> posibleMoves = piece->GetAllPosibleMoves();
		for (int i = 0; i < posibleMoves.size(); i++) {
			std::pair<int, int> coordinates = piece->GetCoordinates();
			std::cout << posibleMoves[i].first << " " << posibleMoves[i].second << " " << piece->GetRepresentation() << "\n";
			if (IsValidMove(coordinates.first, coordinates.second, posibleMoves[i].first, posibleMoves[i].second)) return false;
		}
	}

	return true;
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


void Board::SetPosition(const int& x, const int& y, const int& option) {
	switch (option) {
	case 1:
		board[x][y] = new Queen(turn, x, y);
		break;
	case 2:
		board[x][y] = new Rook(turn, x, y);
		break;
	case 3:
		board[x][y] = new Knight(turn, x, y);
		break;
	case 4:
		board[x][y] = new Bishop(turn, x, y);
		break;
	}
}