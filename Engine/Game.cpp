#include "Game.h"

bool Game::IsValidPiece(int y, int x) const // TODO fix this
{
	return Board::ValidCoordinates(x, y) and board.GetPosition(x, y) != nullptr and board.GetPosition(x, y)->GetColor() == turn;
}

bool Game::IsAValidMove(int originY, int originX, int destinationY, int destinationX)
{
	return board.IsValidMove(originX, originY, destinationX, destinationY, turn);
}

bool Game::Move(int originY, int originX, int destinationY, int destinationX)
{
	return board.Move(originX, originY, destinationX, destinationY, turn);
}

void Game::SwitchTurn()
{
	turn = (turn == Color::White) ? Color::Black : Color::White;
}

void Game::AfterMove()
{
	SwitchTurn();

	isCheck = false;

	if (board.IsCheck(turn)) {
		isCheck = true;
		if (board.IsCheckMate(turn)) {
			isCheckMate = true;
		}
	}
}

void Game::PromotePawn(int destinationX, int destinationY, int option)
{
	std::cout << option << "\n";
	board.SetPosition(destinationY, destinationX, option, turn);
	board.ResetPromotePawn();
}
