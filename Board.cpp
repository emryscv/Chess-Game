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

	board[0][0] = new Rook(Color::Black);
	board[0][1] = new Knight(Color::Black);
	board[0][2] = new Bishop(Color::Black);
	board[0][3] = new Queen(Color::Black);
	board[0][4] = new King(Color::Black);
	board[0][5] = new Bishop(Color::Black);
	board[0][6] = new Knight(Color::Black);
	board[0][7] = new Rook(Color::Black);

	board[1][0] = new Pawn(Color::Black);
	board[1][1] = new Pawn(Color::Black);
	board[1][2] = new Pawn(Color::Black);
	board[1][3] = new Pawn(Color::Black);
	board[1][4] = new Pawn(Color::Black);
	board[1][5] = new Pawn(Color::Black);
	board[1][6] = new Pawn(Color::Black);
	board[1][7] = new Pawn(Color::Black);

	board[6][0] = new Pawn(Color::White);
	board[6][1] = new Pawn(Color::White);
	board[6][2] = new Pawn(Color::White);
	board[6][3] = new Pawn(Color::White);
	board[6][4] = new Pawn(Color::White);
	board[6][5] = new Pawn(Color::White);
	board[6][6] = new Pawn(Color::White);
	board[6][7] = new Pawn(Color::White);

	board[7][0] = new Rook(Color::White);
	board[7][1] = new Knight(Color::White);
	board[7][2] = new Bishop(Color::White);
	board[7][3] = new Queen(Color::White);
	board[7][4] = new King(Color::White);
	board[7][5] = new Bishop(Color::White);
	board[7][6] = new Knight(Color::White);
	board[7][7] = new Rook(Color::White);

	turn = Color::White;
}

bool Board::isValidMove(int originX, int originY, int destinationX, int destinantionY)
{
	//add some logi to check "check"
	if (board[originX][originY]->GetColor() == turn /*and board[originX][originY]->IsValidMove(originX, originY, destinationX, destinantionY)*/ and board[destinationX][destinantionY]->GetColor() != turn)
		return true;
}

void Board::Move(int originX, int originY, int destinationX, int destinantionY)
{
	if (isValidMove(originX, originY, destinationX, destinantionY)) {
		//add some logic to know the piece is no longer in board
		board[destinationX][destinantionY] = board[originX][originY];
		board[originX][originY] = nullptr;
	}
}

void Board::SwitchTurn()
{
	turn = (turn == Color::White) ? Color::Black : Color::White;
}

void Board::PrintBoard()
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
				std::cout << " ";
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
