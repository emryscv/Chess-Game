#include "Game.h"

//int main2(void)
//{
//	Board board;
//	while (true) {
//		system("cls");
//		board.PrintBoard();
//
//		std::cout << "Current Turn: " << (board.GetTurn() == Color::White ? "White" : "Black") << "\n";
//		if (board.GetIsCheck()) std::cout << "Check\n";
//
//		int originX;
//		int originY;
//		int destinationX;
//		int destinationY;
//
//		bool invalid = true;
//		while (invalid) {
//			std::cout << "Select a piece\n";
//			std::cout << "Enter row: ";
//			std::cin >> originX;
//			std::cout << "Enter col: ";
//			std::cin >> originY;
//			if (Board::ValidCoordinates(originX, originY) and board.GetPosition(originX, originY) != nullptr and board.GetPosition(originX, originY)->GetColor() == board.GetTurn()) invalid = false;
//			else {
//				std::cout << "Not one of your pieces!!\n";
//			}
//		}
//
//		invalid = true;
//		while (invalid) {
//			std::cout << "Select a destination\n";
//			std::cout << "Enter row: ";
//			std::cin >> destinationX;
//			std::cout << "Enter col: ";
//			std::cin >> destinationY;
//			if (board.IsValidMove(originX, originY, destinationX, destinationY)) invalid = false;
//			else {
//				std::cout << "Not a valid move!!\n";
//			}
//		}
//
//		board.Move(originX, originY, destinationX, destinationY);
//
//		if (board.GetPromotePawn()) {
//			int option;
//			std::cout << "Pick one:\n1. Queen\n2. Rook\n3. Knight\n4. Bishop\n";
//			std::cin >> option;
//
//			board.SetPosition(destinationX, destinationY, option);
//			board.ResetChangePiece();
//		}
//
//		if (board.GetIsCheck()) board.SetCheck(false);
//
//		board.SwitchTurn();
//
//		if (board.IsCheck(board.GetTurn())) {
//			board.SetCheck(true);
//			if (board.isCheckMate()) {
//				system("cls");
//				std::cout << "Check Mate!!";
//				std::cin >> destinationX;
//			}
//		}
//	}
//	return 0;
//}

bool Game::IsValidPiece(int y, int x) const // TODO fix this
{
	return Board::ValidCoordinates(x, y) and board.GetPosition(x, y) != nullptr and board.GetPosition(x, y)->GetColor() == board.GetTurn();
}

bool Game::IsAValidMove(int originY, int originX, int destinationY, int destinationX)
{
	return board.IsValidMove(originX, originY, destinationX, destinationY);
}

void Game::Move(int originY, int originX, int destinationY, int destinationX)
{
	board.Move(originX, originY, destinationX, destinationY);
	
	if (board.GetPromotePawn()) { //TODO solve this
		int option;
		std::cout << "Pick one:\n1. Queen\n2. Rook\n3. Knight\n4. Bishop\n";
		std::cin >> option;

		board.SetPosition(destinationX, destinationY, option);
		board.ResetChangePiece();
	}
	if (board.GetIsCheck()) board.SetCheck(false);
	
	board.SwitchTurn();
	
	if (board.IsCheck(board.GetTurn())) { //Also solve this
		board.SetCheck(true);
		if (board.isCheckMate()) {
			system("cls");
			std::cout << "Check Mate!!";
			std::cin >> destinationX;
		}
	}
}
